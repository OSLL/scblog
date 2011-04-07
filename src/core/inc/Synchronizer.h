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

/* $Id: Synchronizer.h 53 2011-04-07 13:11:18Z kua $ */
/*!
 * \file Synchronizer.h
 * \brief Header of CSynchronizer
 * \todo add comment here
 *
 * File description
 *
 * PROJ: OSLL/scblog
 * ---------------------------------------------------------------- */

#ifndef _Synchronizer_H_5AC44AE3_757B_431A_8A36_B36F5C58AC23_INCLUDED_
#define _Synchronizer_H_5AC44AE3_757B_431A_8A36_B36F5C58AC23_INCLUDED_

#include <QObject>
#include "LjHandler.h"
#include "ScriboHandler.h"
#include "ConferenceHandler.h"
#include "Post.h"

namespace core
{
  #define BIT(a) (1 << (a))

  enum BloggingObjects{
     REPORTS,
     LJ_POSTS,
     SCRIBO_POSTS
  };

  /*!
   * Class description. May use HTML formatting
   *
   */
  class CSynchronizer: public QObject
  {
    Q_OBJECT

    BlogService::CLjHandler* m_ljHandler;
    SmartSpace::CConferenceHandler* m_conferenceHandler;
    SmartSpace::CScriboHandler* m_scriboHandler;

    int m_loadingFlags;

    QSet<CPost> m_reports;
    QSet<CPost> m_ljPosts;
    QSet<CPost> m_ssPosts;

    void synchronizePosts();

  private slots:

    void reciveReports(QSet<core::CPost>);
    void reciveLjPosts(QSet<core::CPost>);
    void reciveSsPosts(QSet<core::CPost>);

  public:
    CSynchronizer();
    ~CSynchronizer(){};
    
    void requestPostSynchronization();

  }; // class CSynchronizer

} // namespace core

#endif //_Synchronizer_H_5AC44AE3_757B_431A_8A36_B36F5C58AC23_INCLUDED_
/* ===[ End of file $HeadURL: svn+ssh://kua@osll.spb.ru/svn/scblog/trunk/src/core/inc/Synchronizer.h $ ]=== */
