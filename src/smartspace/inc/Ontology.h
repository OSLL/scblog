/*
 * Copyright В© 2011 Yury Korolev yury.king@gmail.com
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

/* $Id: Ontology.h 66 2011-04-26 19:07:12Z kua $ */
/*!
 * \file Ontology.h
 * \brief Header of COntology
 * \todo add comment here
 *
 * File description
 *
 * PROJ: OSLL/scblog
 * ---------------------------------------------------------------- */

#ifndef _Ontology_H_D7E9B056_E9D3_4890_B3F4_00E0BF5E3F79_INCLUDED_
#define _Ontology_H_D7E9B056_E9D3_4890_B3F4_00E0BF5E3F79_INCLUDED_

#include <QObject>

namespace SmartSpace
{
  // old predicates & notification
  /*
  static const QString ACCOUNT_LOGIN = "osll";
  static const QString ACCOUNT_PASSWORD = "scblog1861";

  static const QString ANY = "sib:any";
  static const QString TYPE = "rdf:type";

  // Overlay Ontology
  static const QString DESCRIBE = "describe";

  // Smart Conference Ontology
  static const QString HAS_USER = "have";
  static const QString HAS_NAME = "is";
  static const QString EMAIL = "email";
  static const QString PHONE = "phone";
  static const QString HAS_PRESENTATION = "presents";
  static const QString URL = "url";
  static const QString PRESENTATION_TITLE = "Title";
  static const QString KEYWORDS = "Keywords";

  // Scribo Ontology
  static const QString BLOG_SERVICE_NAME ="NotificationSCLJ";
  static const QString ACCOUNT_NAME ="account-sclj";
  static const QString PERSON_NAME ="person-sclj";
  static const QString POST ="scribo_Post";
  static const QString COMMENT ="scribo_Comment";
  static const QString TITLE = "scribo_title";
  static const QString TEXT = "scribo_text";
  static const QString HAS_COMMENT = "scribo_hasComment";
  static const QString HAS_POST = "scribo_hasPost";
  static const QString POSTER = "scribo_poster";
  static const QString LOGIN = "scribo_login";
  static const QString PASSWORD = "scribo_password";
  static const QString SCRIBO_TYPE = "scribo_type";
  
  static const QString ACCOUNT_TYPE = "foaf_account";
  static const QString PERSON_INFORMATION = "scribo_personInformation";

  // Scribo Notifications
  static const QString REFRESH_COMMENTS = "refreshComments";
  static const QString REFRESH_POSTS = "refreshPosts";
  static const QString SEND_COMMENT = "sendComment";
  static const QString COMMENT_ID = "comId";
  static const QString PARENT_ID = "parId";
  static const QString NOTIFICATION = "Notification-";
  */

  // new preficates
  static const QString ACCOUNT_LOGIN = "osll";
  static const QString ACCOUNT_PASSWORD = "scblog1861";

  static const QString ANY = "sib:any";
  static const QString TYPE = "rdf:type";

  // Overlay Ontology
  static const QString DESCRIBE = "describe";

  // Smart Conference Ontology
  static const QString HAS_USER = "have";
  static const QString HAS_NAME = "is";
  static const QString EMAIL = "email";
  static const QString PHONE = "phone";
  static const QString HAS_PRESENTATION = "presents";
  static const QString URL = "url";
  static const QString PRESENTATION_TITLE = "Title";
  static const QString KEYWORDS = "Keywords";

  // Scribo Ontology


  // аккаунт пользователя (Person)

  // фиксированное имя (часть онтологии), по которому клиенты SmartScribo
  // могут получить доступ к онтологическим даннымs
  static const QString ACCOUNT_NAME ="account-sclj";    //
  static const QString ONLINE_ACCOUNT_TYPE ="http://xmlns.com/foaf/0.1/OnlineAccount";
  static const QString LOGIN = "http://www.cs.karelia.ru/smartscribo#login";
  static const QString PASSWORD = "http://www.cs.karelia.ru/smartscribo#password";

  static const QString PERSON_NAME ="person-sclj";  // сущность Person, содержит аккаунты

  static const QString POST ="http://www.cs.karelia.ru/smartscribo#Post";
  static const QString COMMENT ="http://www.cs.karelia.ru/smartscribo#Comment";
  static const QString TITLE = "http://www.cs.karelia.ru/smartscribo#title";
  static const QString TEXT = "http://www.cs.karelia.ru/smartscribo#text";
  static const QString HAS_COMMENT = "http://www.cs.karelia.ru/smartscribo#hasComment";
  static const QString HAS_POST = "http://www.cs.karelia.ru/smartscribo#hasPost";
  static const QString POSTER = "http://www.cs.karelia.ru/smartscribo#poster";

  static const QString SCRIBO_TYPE = "type";    // not used now

  // свойство, которое связывает person и аккаунт
  static const QString ACCOUNT_TYPE = "http://xmlns.com/foaf/0.1/account";  // foaf_account
  static const QString PERSON_INFORMATION = "http://www.cs.karelia.ru/smartscribo#personInformation";

  // Scribo Notifications
  // константа используется для получения нотификацией блог-процессором.
  static const QString BLOG_SERVICE_NAME ="Notification-SCLJ";
  static const QString REFRESH_COMMENTS = "http://www.cs.karelia.ru/smartscribo#refreshComments";
  static const QString REFRESH_POSTS = "http://www.cs.karelia.ru/smartscribo#refreshPosts";
  static const QString SEND_COMMENT = "http://www.cs.karelia.ru/smartscribo#sendComment";
  static const QString COMMENT_ID = "http://www.cs.karelia.ru/smartscribo#comId";
  static const QString PARENT_ID = "http://www.cs.karelia.ru/smartscribo#parId";
  static const QString NOTIFICATION = "http://www.cs.karelia.ru/smartscribo#Notification";

} // namespace smartspace

#endif //_Ontology_H_D7E9B056_E9D3_4890_B3F4_00E0BF5E3F79_INCLUDED_

/* ===[ End of file $HeadURL: svn+ssh://kua@osll.spb.ru/svn/scblog/trunk/src/smartspace/inc/Ontology.h $ ]=== */
