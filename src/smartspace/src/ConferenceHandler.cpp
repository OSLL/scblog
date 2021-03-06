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
 * $Id: ConferenceHandler.cpp 67 2011-05-02 20:09:17Z kua $ 
 *
 * \file ConferenceHandler.cpp
 * \brief CConferenceHandler implementation
 *
 * File description
 *
 * PROJ: OSLL/scblog
 * ---------------------------------------------------------------- */

#include <QDebug>
#include <QTimer>
#include "Ontology.h"
#include "ConferenceHandler.h"

namespace SmartSpace
{
  static const QString CONFERENCE_SUBSCRIPTION = "scheduleChanges";

  CConferenceHandler::CConferenceHandler(QString sibUri, QObject *parent) :
    CSSHandler(sibUri, parent)
  {
    m_postProcessor = NULL;
  }

  CConferenceHandler::~CConferenceHandler()
  {
  }

  void CConferenceHandler::checkExistingReports()
  {
    qDebug() << "checkExistingReports";

    m_queryList.clear();
    m_queryList.append(createDefaultTriple(ANY, HAS_USER, ANY));

    m_postProcessor = &CConferenceHandler::recieveReports;
    QTimer::singleShot(1, this, SLOT(query()));
  }

  void CConferenceHandler::recieveReports(QList<Triple *> triples)
  {
    qDebug() << "recieveReports";

    for(QList<Triple *>::iterator it = triples.begin(); it != triples.end(); ++it)
      m_reports.insert((*it)->object().node());

    if (m_reports.isEmpty())
      m_postProcessor = NULL;
    else
      loadReports();
  }

  void CConferenceHandler::postProcess(QList<Triple *> triples)
  {
    if(m_postProcessor != NULL)
      (this->*m_postProcessor)(triples);
  }

  bool CConferenceHandler::isReady()
  {
    return m_postProcessor == NULL;
  }

  void CConferenceHandler::loadReports()
  {
    qDebug() << "CConferenceHandler::loadReports";

    m_queryList.clear();

    for(QSet<QString>::iterator it = m_reports.begin(); it != m_reports.end(); ++it)
    {
      QString userId = *it;

      QSharedPointer<core::CReport> post =  QSharedPointer<core::CReport>(new core::CReport());
      post->setUserId(userId);

      m_posts[userId] = post;

      m_queryList.push_back(createDefaultTriple(userId, HAS_NAME, ANY));
      m_queryList.push_back(createDefaultTriple(userId, EMAIL, ANY));
      m_queryList.push_back(createDefaultTriple(userId, PHONE, ANY));
      m_queryList.push_back(createDefaultTriple(userId, HAS_PRESENTATION, ANY));
    }

    m_postProcessor = &CConferenceHandler::processUserProfile;
    QTimer::singleShot(1, this, SLOT(query()));
  }

  void CConferenceHandler::processUserProfile(QList<Triple *> triple)
  {
    qDebug() << "processUserProfile";

    m_queryList.clear();

    for(QList<Triple *>::iterator it = triple.begin(); it != triple.end(); ++it)
    {
      QString userId = (*it)->subject().node();

      if((*it)->predicate().node() == HAS_PRESENTATION)
      {
        QString reportId = (*it)->object().node();

        m_presentationsCache.insert(reportId,userId);

        m_queryList.push_back(createDefaultTriple(reportId, URL, ANY));
        m_queryList.push_back(createDefaultTriple(reportId, PRESENTATION_TITLE, ANY));
        m_queryList.push_back(createDefaultTriple(reportId, KEYWORDS, ANY));
      }

      m_posts[userId]->putUserData((*it)->predicate().node(), (*it)->object().node());
    }
    m_postProcessor = &CConferenceHandler::processPresentation;
    QTimer::singleShot(1, this, SLOT(query()));
  }

  void CConferenceHandler::processPresentation(QList<Triple *> triple)
  {
    qDebug() << "processPresentation";

    m_queryList.clear();

    for(QList<Triple *>::iterator it = triple.begin(); it != triple.end(); ++it)
    {
      QString presentatonId = (*it)->subject().node();
      QString userId = m_presentationsCache.value(presentatonId);

      m_posts[userId]->putPresentationData((*it)->predicate().node(), (*it)->object().node());
      m_posts[userId]->generatePostData();
    }

    for(QMap<QString, QSharedPointer<core::CReport> >::const_iterator it = m_posts.begin(); it != m_posts.end(); ++it)
    {
      QString s;

      QTextStream os(&s);
      os << *it.value();

      qDebug() << s;
    }

    m_postProcessor = NULL;

    emit loadReportsDone(m_posts.values());
    m_posts.clear();
  }

} // namespace smartspace

/* ===[ End of file $HeadURL: svn+ssh://kua@osll.spb.ru/svn/scblog/trunk/src/smartspace/src/ConferenceHandler.cpp $ ]=== */
