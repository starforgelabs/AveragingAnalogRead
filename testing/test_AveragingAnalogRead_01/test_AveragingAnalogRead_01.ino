#include <ArduinoUnit.h>
#include <BaseAnalogRead.h>
#include <BufferedAnalogRead.h>
#include <AveragingAnalogRead.h>

TestSuite suite;

class TestAveragingAnalogRead: public AveragingAnalogRead
{
  public:
    int* getBuffer() { return _Buffer; }
    byte Count() { return AveragingAnalogRead::Count(); }
    unsigned long Total() { return AveragingAnalogRead::Total(); }
};

TestAveragingAnalogRead tester;

int insert(int aValue)
{
  return tester.Read(aValue);
}

test(clear)
{
  // Fill with data
  for(int i=0; i<1024; i++)
    insert(i);
  
  // Test
  tester.Clear();
  assertEquals(0, tester.Count());
  assertEquals(0, tester.Total());
}

test(average1)
{
  int val;

  // Fill with data
  for(int i=0; i<1024; i++)
    insert(i);
  
  tester.setBufferSize(2);
  assertEquals(0, tester.Total());
  assertEquals(0, tester.Count());

  val = insert(10);
  assertEquals(10, val);   
  assertEquals(10, tester.Total());
  assertEquals(1, tester.Count());

  val = insert(0);
  assertEquals(5, val);
  assertEquals(10, tester.Total());
  assertEquals(2, tester.Count());

  val = insert(0);
  assertEquals(0, val);
  assertEquals(0, tester.Total());
  assertEquals(2, tester.Count());

  val = insert(1);
  assertEquals(1, val);
  assertEquals(1, tester.Total());
  assertEquals(2, tester.Count());
}

test(average2)
{
  int val;

  // Fill with data
  for(int i=0; i<1024; i++)
    insert(i);
  
  tester.setBufferSize(4);
  assertEquals(0, tester.Total());
  assertEquals(0, tester.Count());

  val = insert(0);
  assertEquals(0, val);
  assertEquals(0, tester.Total());
  assertEquals(1, tester.Count());

  val = insert(0);
  assertEquals(0, val);
  assertEquals(0, tester.Total());
  assertEquals(2, tester.Count());

  val = insert(0);
  assertEquals(0, val);
  assertEquals(0, tester.Total());
  assertEquals(3, tester.Count());

  val = insert(0);
  assertEquals(0, val);
  assertEquals(0, tester.Total());
  assertEquals(4, tester.Count());

  val = insert(1);
  assertEquals(0, val);
  assertEquals(1, tester.Total());
  assertEquals(4, tester.Count());

  val = insert(1);
  assertEquals(1, val);
  assertEquals(2, tester.Total());
  assertEquals(4, tester.Count());

  val = insert(1);
  assertEquals(1, val);
  assertEquals(3, tester.Total());
  assertEquals(4, tester.Count());

  val = insert(1);
  assertEquals(1, val);
  assertEquals(4, tester.Total());
  assertEquals(4, tester.Count());

  val = insert(1);
  assertEquals(1, val);
  assertEquals(4, tester.Total());
  assertEquals(4, tester.Count());

  val = insert(1);
  assertEquals(1, val);
  assertEquals(4, tester.Total());
  assertEquals(4, tester.Count());
}

test(setbuffersize)
{
  // Fill with data
  for(int i=0; i<1024; i++)
    insert(i);
  
  // Test
  tester.setBufferSize(8);
  assertEquals(0, tester.Count());
  assertEquals(0, tester.Total());
}

void setup()
{
}

void loop()
{
  suite.run();
}

