/*
 * Copyright © 2011 Yury Korolev yury.king@gmail.com
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * 3. The name of the author may not be used to endorse or promote
 *    products derived from this software without specific prior written
 *    permission.
 *
 * The advertising clause requiring mention in adverts must never be included.
 */

/*! ---------------------------------------------------------------
 * $Id: BlogProcessor.cpp 67 2011-05-02 20:09:17Z kua $ 
 *
 * \file BlogProcessor.cpp
 * \brief CBlogProcessor implementation
 *
 * File description
 *
 * PROJ: OSLL/scblog
 * ---------------------------------------------------------------- */

#include <QDebug>
#include <QTimer>
#include <QSet>
#include <QFile>
#include "BlogProcessor.h"
#include "Id.h"
#include "Ontology.h"
#include "Configurator.h"

namespace core
{
  static const QString SERIALIZE_FILE_NAME = "scblog.dat";

  void CBlogProcessor::init()
  {
    CConfigurator configurator;
    m_configurationMap = configurator.getConfigurations();

    if (!m_configurationMap.size())
    {
      qDebug() << "Error loading configuration data";

      return;
    }

    initLjManager();
  }

  void CBlogProcessor::initLjManager()
  {
    m_ljManager = new BlogService::CLjManager(this);

    QSharedPointer<BlogService::CLjHandler> ljHandler =
        QSharedPointer<BlogService::CLjHandler> (
            new BlogService::CLjHandler(m_configurationMap["LIVE_JOURNAL_URL"],
                                        m_configurationMap["LIVE_JOURNAL_LOGIN"],
                                        m_configurationMap["LIVE_JOURNAL_PASSWORD"], m_ljManager));

    if (!m_configurationMap["PROXY_SERVER_NAME"].isEmpty() && !m_configurationMap["PROXY_PORT"].isEmpty())
      ljHandler->setProxy(m_configurationMap["PROXY_SERVER_NAME"], m_configurationMap["PROXY_PORT"].toInt());

    m_ljManager->setHandler(ljHandler);

    m_postsCounter = 0;

    QObject::connect(ljHandler.data(), SIGNAL(loadPostsDone(QList<QSharedPointer<core::CPost> >)), this,
      SLOT(reciveLjPosts(QList<QSharedPointer<core::CPost> >)));
    QObject::connect(ljHandler.data(), SIGNAL(loadCommentsDone(QList<QSharedPointer<core::CComment> >)), this,
      SLOT(reciveLjComments(QList<QSharedPointer<core::CComment> >)));
    QObject::connect(ljHandler.data(), SIGNAL(sendPostDone(core::CId, QSharedPointer<core::CPost>)), this,
      SLOT(storePost(core::CId, QSharedPointer<core::CPost>)));
    QObject::connect(ljHandler.data(), SIGNAL(sendCommentDone(core::CId, QSharedPointer<core::CComment>)), this,
      SLOT(storeComment(core::CId, QSharedPointer<core::CComment>)));

    loadExistingLjPosts();
  }

  void CBlogProcessor::initConferenceHandler()
  {
    m_conferenceHandler = new SmartSpace::CConferenceHandler(m_configurationMap["SMART_CONFERENCE_ID"], this);

    QObject::connect(m_conferenceHandler, SIGNAL(loadReportsDone(QList<QSharedPointer<core::CReport> >)), this,
      SLOT(reciveReports(QList<QSharedPointer<core::CReport> >)));

    m_conferenceHandler->checkExistingReports();
  }

  void CBlogProcessor::initScriboHandler()
  {
    qDebug() << "initScriboHandler";

    m_scriboHandler = new SmartSpace::CScriboHandler(m_configurationMap["SMART_SCRIBO_ID"], this);
    m_scriboHandler->subscribeRefreshComments();
    m_scriboHandler->subscribeSendComment();

    QObject::connect(m_scriboHandler, SIGNAL(loadPostsDone(QList<QSharedPointer<core::CPost> >)), this,
      SLOT(reciveSsPosts(QList<QSharedPointer<core::CPost> >)));
    QObject::connect(m_scriboHandler, SIGNAL(loadCommentsDone(QList<QSharedPointer<core::CComment> >)), this,
      SLOT(reciveSsComments(QList<QSharedPointer<core::CComment> >)));
    QObject::connect(m_scriboHandler, SIGNAL(refreshComments()), this, SLOT(refreshComments()));
  }

  void CBlogProcessor::initUpdateByTimer()
  {
    m_timer = new QTimer(this);
    m_timer->start((m_configurationMap["UPDATE_FREQUENCY"].toInt())*1000);

    QObject::connect(m_timer,SIGNAL(timeout()), this, SLOT(refreshByTimer()));
  }

  void CBlogProcessor::refreshByTimer()
  {
    if(m_ljManager->isWait())
      refreshComments();
  }

  void CBlogProcessor::reciveReports(QList<QSharedPointer<core::CReport> > posts)
  {
    qDebug() << "CBlogProcessor::reciveReports";

    m_reports.clear();
    foreach(QSharedPointer<core::CReport> post, posts)
    {
      qDebug()  << post->title();
      m_reports.push_back(post);
    }

    m_conferenceHandler->leave();

    initScriboHandler();

    m_scriboHandler->replyToNotification(SmartSpace::REFRESH_POSTS, "ok");
    m_scriboHandler->loadPosts(SmartSpace::ACCOUNT_NAME);

    initUpdateByTimer();
  }

  bool CBlogProcessor::checkBlogObjectContains(const CId id)
  {
    QList<CId>::iterator it = m_idList.begin();
    bool flag = false;

    while((it != m_idList.end()) && (!flag))
    {
      if(*it == id)
        flag = true;

      ++it;
    }

    return flag;
  }

  CId CBlogProcessor::getFullId(const CId id)
  {
    QList<CId>::iterator it = m_idList.begin();

    while(it != m_idList.end())
    {
      if(*it == id)
        return *it;

      ++it;
    }

    return id;
  }

  void CBlogProcessor::reciveLjComments(QList<QSharedPointer<core::CComment> > comments)
  {
    qDebug() << "CBlogProcessor::reciveLjComments";

    foreach(QSharedPointer<core::CComment> comment, comments)
      if(!checkBlogObjectContains(*comment->id()))
      {
        comment->generateSsId();
        m_toSsList.push_back(comment);
      }

    saveCommentToSs();

    m_postsCounter++;

    if(m_postsCounter == m_postIds.size())
    {
      m_scriboHandler->replyToNotification(SmartSpace::REFRESH_COMMENTS, "ok");
      m_postsCounter = 0;
    }

    printSerializedMap();
  }

  void CBlogProcessor::reciveSsComments(QList<QSharedPointer<core::CComment> > comments)
  {
    qDebug() << "CBlogProcessor::reciveSsComments";

    foreach(QSharedPointer<CComment> comment, comments)
      if(!checkBlogObjectContains(*comment->id()))
        saveCommentToLj(comment);
  }

  void CBlogProcessor::reciveSsPosts(QList<QSharedPointer<core::CPost> > posts)
  {
    qDebug() << "CBlogProcessor::reciveSsPosts";

    QList<QString> existingReports;

    foreach(QSharedPointer<core::CReport> report, m_reports)
      foreach(QSharedPointer<core::CPost> post, posts)
        if (post->title().toUtf8() == report->title().toUtf8())
          existingReports.push_back(report->title());
   
    foreach(QSharedPointer<core::CReport> report, m_reports)
      if (!existingReports.count(report->title()))
      {
        m_scriboHandler->sendBlogObject(report);
        posts.push_back(report);
      }

    foreach(QSharedPointer<core::CPost> post, posts)
    {
      qDebug() << post->title();
      if(!checkBlogObjectContains(*post->id()))
      {
        qDebug() << "CBlogProcessor::newPost";

        if(m_existingLjPosts.contains(post->title()))
        {
          qDebug() << "CBlogProcessor::existingLjPost";

          QSharedPointer<core::CPost> ljPost = m_existingLjPosts.value(post->title());
          post->id()->setLjId(ljPost->id()->ljId());

          storePost(*post->id(), post);
        }
        else
          m_ljManager->sendPost(post);
      }
    }
  }

  void CBlogProcessor::refreshComments()
  {
    qDebug() << "CBlogProcessor::refreshComments";

    if(!m_ljManager->isLoadComment())
      foreach(CId id, m_postIds)
        m_ljManager->loadComments(id);
  }

  bool CBlogProcessor::setParent(QSharedPointer<CComment> comment, bool copyPostId = false)
  {
    qDebug() << "CBlogProcessor::setParent";
    qDebug() << "parentId" << comment->parentId()->ljId() << comment->parentId()->ssId();

    if(!checkBlogObjectContains(*comment->parentId()))
      return false;

    CId parentId = getFullId(*comment->parentId());

    if(parentId.isComlete())
    {
      comment->setParentId(QSharedPointer<CId>(new CId(parentId)));

      if(copyPostId)
      {
        QString postId = parentId.postId().isEmpty() ? parentId.ljId() : parentId.postId();
        comment->id()->setPostId(postId);
      }
      return true;
    }

    return false;
  }

  void CBlogProcessor::saveCommentToSs()
  {
    qDebug() << " CBlogProcessor::saveCommentToSs";

    while(!m_toSsList.isEmpty())
    {
      QList<QSharedPointer<CComment> > temp = m_toSsList;

      for(QList<QSharedPointer<CComment> >::iterator iter = temp.begin(); iter != temp.end(); ++iter)
        if(setParent(*iter))
        {
          m_scriboHandler->sendBlogObject(*iter);
          storeBlogObject(*(*iter)->id(), *iter);
          m_toSsList.removeOne(*iter);

          QString s;

          QTextStream os(&s);
          os << **iter;
          qDebug() << s;
        }
    }
  }

  void CBlogProcessor::storeBlogObject(CId id, QSharedPointer<IBlogObject> blogObject)
  {
    m_blogObjects.insert(id, blogObject);
    m_idList.push_back(id);
    serialize();
  }

  void CBlogProcessor::saveCommentToLj(QSharedPointer<CComment> comment)
  {
    if(setParent(comment, true))
      m_ljManager->sendComment(comment);
  }

  void CBlogProcessor::storePost(core::CId id, QSharedPointer<core::CPost> post)
  {
    qDebug() << "CBlogProcessor::storePost";

    storeBlogObject(id, post);
    m_postIds.push_back(id);
  }

  void CBlogProcessor::storeComment(core::CId id, QSharedPointer<core::CComment> comment)
  {
    qDebug() << "CBlogProcessor::storeComment";

    storeBlogObject(id, comment);
    m_scriboHandler->saveParentRelations(comment);
    m_scriboHandler->replyToNotification(SmartSpace::SEND_COMMENT, "ok");
  }

  void CBlogProcessor::loadExistingLjPosts()
  {
    qDebug() << "CBlogProcessor::loadExistingLjPosts()";

    m_ljManager->loadPosts();
  }

  void CBlogProcessor::reciveLjPosts(QList<QSharedPointer<core::CPost> > posts)
  {
    qDebug() << "CBlogProcessor::reciveLjPosts";

    foreach(QSharedPointer<core::CPost> post, posts)
    {
      m_existingLjPosts[post->title()] = post;

      QString s;

      QTextStream os(&s);
      os << *post;
      qDebug() << s;
    }

    initConferenceHandler();
  }

  void CBlogProcessor::printSerializedMap()
  {
    qDebug() << "Map Size" << m_blogObjects.size();
    for(QMap<CId, QSharedPointer<IBlogObject> >::iterator iter = m_blogObjects.begin(); iter != m_blogObjects.end();
        ++iter)
    {
      QString s;

      QTextStream os(&s);
      os << **iter;
      qDebug() << s;
    }
  }

  void CBlogProcessor::serialize()
  {
    QFile file(SERIALIZE_FILE_NAME);
    file.remove();
    file.open(QIODevice::WriteOnly);
    QDataStream out(&file);
    out << m_idList;
    file.close();
  }

  void CBlogProcessor::deserialize()
  {
    QFile file(SERIALIZE_FILE_NAME);
    if(file.exists())
    {
      file.open(QIODevice::ReadOnly);
      QDataStream in(&file);
      in >> m_idList;
    }
    file.close();

    foreach(CId id, m_idList)
      if(id.isPost())
        m_postIds.push_back(id);
  }
} // namespace core

/* ===[ End of file $HeadURL: svn+ssh://kua@osll.spb.ru/svn/scblog/trunk/src/core/src/BlogProcessor.cpp $ ]=== */
