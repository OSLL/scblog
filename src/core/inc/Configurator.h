/*
 * Copyright © 2012 Yury Korolev yury.king@gmail.com
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

/* $Id$ */
/*!
 * \file Configurator.h
 * \brief Header of CConfigurator
 * \todo add comment here
 *
 * File description
 *
 * PROJ: OSLL/scblog
 * ---------------------------------------------------------------- */

#ifndef _Configurator_H_D9A59F26_0B4A_4BDE_B67A_A62410EDB003_INCLUDED_
#define _Configurator_H_D9A59F26_0B4A_4BDE_B67A_A62410EDB003_INCLUDED_

#include <QObject>
#include <QDomDocument>
#include <QMap>

namespace core
{
 /*!
   * Class description. May use HTML formatting
   *
   */
  class CConfigurator:
    public QObject
  {
    Q_OBJECT

    QDomDocument m_document;

    bool loadConfigurations();

  public:
    QMap<QString, QString> getConfigurations();

  }; // class CConfigurator
} // namespace core

#endif //_Configurator_H_D9A59F26_0B4A_4BDE_B67A_A62410EDB003_INCLUDED_

/* ===[ End of file $HeadURL$ ]=== */
