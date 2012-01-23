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

/*! ---------------------------------------------------------------
 * $Id$ 
 *
 * \file Configurator.cpp
 * \brief CConfigurator implementation
 *
 * File description
 *
 * PROJ: OSLL/scblog
 * ---------------------------------------------------------------- */

#include <QString>
#include <QFile>
#include <QDebug>
#include "Configurator.h"

namespace core
{
  static const QString CONFIGURATION_FILE_NAME = "scblog.conf";

  bool CConfigurator::loadConfigurations()
  {
    qDebug() << "CConfigurator::loadConfigurations";

    QFile file(CONFIGURATION_FILE_NAME);

    if (!file.open(QIODevice::ReadOnly))
      return false;

    if (!m_document.setContent(&file))
    {
      file.close();

      return false;
    }

    file.close();

    return true;
  }

  QMap<QString, QString> CConfigurator::getConfigurations()
  {
    qDebug() << "CConfigurator::getConfigurations";

    QMap<QString, QString> result;

    if (!loadConfigurations())
      return result;

    QDomElement root = m_document.documentElement();
    QDomNode node = root.firstChild();

    while(!node.isNull())
    {
      result.insert(node.attributes().item(1).nodeValue(), node.attributes().item(0).nodeValue());
      node = node.nextSibling();
    }

    return result;
  }

} // namespace core

/* ===[ End of file $HeadURL$ ]=== */
