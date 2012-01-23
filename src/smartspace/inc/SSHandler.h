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

/* $Id: SSHandler.h 65 2011-04-25 19:46:33Z kua $ */
/*!
 * \file CSSHandler.h
 * \brief Header of CSSHandler
 * \todo add comment here
 *
 * File description
 *
 * PROJ: OSLL/scblog
 * ---------------------------------------------------------------- */

#ifndef _SSHandler_H_4B8A8DF5_31AA_48E3_B649_F1BED3CDFFA2_INCLUDED_
#define _SSHandler_H_4B8A8DF5_31AA_48E3_B649_F1BED3CDFFA2_INCLUDED_

#include <QObject>
#include <QMap>
#include <QPair>
#include <QQueue>
#include <QSharedPointer>
#include "q_whiteboard_node.h"
#include "templatequery.h"
#include "templatesubscription.h"
#include "wqlvaluesquery.h"
#include "wqlrelatedquery.h"

#include "Post.h"
#include "Comment.h"

namespace SmartSpace
{
  /*!
   * Class description. May use HTML formatting
   *
   */
  class CSSHandler: public QObject
  {
    Q_OBJECT

    QSharedPointer<QWhiteBoardNode> m_node;

    QHash<QString, QSharedPointer<TemplateQuery> > m_queries;
    QHash<QString, QSharedPointer<WqlValuesQuery> > m_wqlQueries;
    QHash<QString, QSharedPointer<TemplateSubscription> > m_subscriptions;

    QQueue< QPair<TripleElement, QString > > m_wqlQueryQueue;

    virtual void postProcess(QList<Triple *> triples) =0;

  private slots:
    void queryDone(int success);
    void query();
    void wqlQuery();
    void processProfileIds(int result);

  signals:
    void loadProfilesDone(QSet<QString>);

  public:
    CSSHandler(QObject *parent = 0) : QObject(parent) {};
    CSSHandler(QString sibUri, QObject *parent = 0);
    ~CSSHandler();

    void wqlQuery(QString element, QString query, const char* member);

    QList<Triple *> m_queryList;

    void join(QString sibUri);
    void leave();
    void insert(Triple* triple);
    void insert(QList<Triple*> triplets);
    void remove(QList<Triple*> list);
    void query(Triple* triple);
    QSharedPointer<QWhiteBoardNode> getNode();
    QSharedPointer<TemplateSubscription> creatreSubscription(QString name);
    QSharedPointer<TemplateQuery> creatreQuery(QString name);
    QSharedPointer<TemplateSubscription> getSubscription(QString name);
    QSharedPointer<TemplateQuery> getQuery(QString name);
    QSharedPointer<WqlValuesQuery> getWqlQuery(QString name);
    void deleteQuery(QString name);

    static Triple* createDefaultTriple(QString subject, QString predicat, QString object);
    static Triple* createLiteralTriple(QString subject, QString predicat, QString object);
    static QList<Triple *> createTripleList(Triple *triple);

  }; // class CSSHandler
} // namespace SmartSpace

#endif //_SSHandler_H_4B8A8DF5_31AA_48E3_B649_F1BED3CDFFA2_INCLUDED_
/* ===[ End of file $HeadURL: svn+ssh://kua@osll.spb.ru/svn/scblog/trunk/src/smartspace/inc/SSHandler.h $ ]=== */
