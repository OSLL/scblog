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

/* $Id: LjHandler.h 53 2011-04-07 13:11:18Z kua $ */
/*!
 * \file LjHandler.h
 * \brief Header of CLjHandler
 * Class to implement the basic operations with LiveJournal
 *
 * File description
 *
 * PROJ: OSLL/scblog
 * ---------------------------------------------------------------- */

#ifndef _LjHandler_H_0BA429DB_4352_41E7_81A2_C3F5DBDDE350_INCLUDED_
#define _LjHandler_H_0BA429DB_4352_41E7_81A2_C3F5DBDDE350_INCLUDED_

#include <QString>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QSet>
#include "Post.h"
#include "Comment.h"

namespace BlogService
{
  /*!
   * Class description. May use HTML formatting
   *
   */
  class CLjHandler: public QObject
  {
    Q_OBJECT

    QNetworkAccessManager* m_networkManager;
    QUrl m_url;
    QString m_userName;
    QString m_password;

    QList<core::CPost> m_postsBuffer;
    QList<core::CComment> m_commentsBuffer;
    core::CPost m_post;

    void (CLjHandler::*m_postProcessor)(QString);

    QString computeMD5(QString input);
    void sendRequest(QByteArray textRequest);
    void getChallenge();
    QString getAuthResponse(QString password, QString challenge);

    void getPosts(QString response);
    void processPosts(QString response);
    void sendPost(QString response);

    void getComments(QString response);
    void processComments(QString response);
    void sendComment(QString response);

    void sessionGenerate(QString response);
    void loginWithCookies(QString response);
    void loginChallenge(QString response);

    QMap<QString, QString> initParametersMap(QString challengeResponse);

  private slots:

    void httpDone(QNetworkReply*);

  signals:
  void loadPostsDone(QSet<core::CPost> posts);

  public:

    CLjHandler(QString serviceUrl, QString userName, QString password, QObject *parent = 0);

  public slots:
    void login();

    void loadComments(core::CPost post);
    void loadPosts();
    void sendPost(core::CPost post);
    void sendComment(core::CComment comment);

  }; // class CLjHandler
} // namespace BlogService

#endif //_LjHandler_H_0BA429DB_4352_41E7_81A2_C3F5DBDDE350_INCLUDED_
/* ===[ End of file $HeadURL: svn+ssh://kua@osll.spb.ru/svn/scblog/trunk/src/blogservice/inc/LjHandler.h $ ]=== */
