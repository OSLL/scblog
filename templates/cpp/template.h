/*
 * Copyright © ${YEAR} <name of author> <e-mail>
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
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
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

/* \$Id$ */
/*!
 * \file ${NAMEH}
 * \brief Header of C${NAME}
 * \todo add comment here
 *
 * File description
 *
 * PROJ: OSLL/scblog
 * ---------------------------------------------------------------- */

#ifndef _${NAME}_H_${UUID}_INCLUDED_
#define _${NAME}_H_${UUID}_INCLUDED_

#include <QObject>

namespace ${PACKAGE}
{
 /*!
   * Class description. May use HTML formatting
   *
   */
  class C${NAME}:
    public QObject
  {
    Q_OBJECT

  public:
    C${NAME}()
    {
    }

    ~C${NAME}()
    {
    }
    
  private:    
    C${NAME}(const C${NAME}& obj);
    C${NAME}& operator=(const C${NAME}& obj);

  }; // class C${NAME}
  
} // namespace ${PACKAGE}

#endif //_${NAME}_H_${UUID}_INCLUDED_

/* ===[ End of file \$HeadURL$ ]=== */
