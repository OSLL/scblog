/* \$Id$ */
/*!
 * \file ${FTEST}
 * \brief Test suite for ${CLASS} class
 *
 * PROJ: OSLL/scblog
 * ----------------------------------------------------------- */

#if !defined(${GUID})
#define ${GUID}

#include <QtTest/QtTest>

namespace Test
{
  class ${CLASS}Test: 
    public QObject
  {
    Q_OBJECT

  private slots:
    
    void initTestCase();
    void cleanupTestCase();
    
  };//class ${CLASS}Test  
}//namespace Test

#endif // ${GUID}

/* ===[ End of file \$HeadURL$ ]=== */
