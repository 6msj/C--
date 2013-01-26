/*
 *  Test.cp
 *  Test
 *
 *  Created by James Nguyen on 1/26/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#include <iostream>
#include "Test.h"
#include "TestPriv.h"

void Test::HelloWorld(const char * s)
{
	 TestPriv *theObj = new TestPriv;
	 theObj->HelloWorldPriv(s);
	 delete theObj;
};

void TestPriv::HelloWorldPriv(const char * s) 
{
	std::cout << s << std::endl;
};

