/*
 *  TestPriv.h
 *  Test
 *
 *  Created by James Nguyen on 1/26/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

/* The classes below are not exported */
#pragma GCC visibility push(hidden)

class TestPriv
{
	public:
		void HelloWorldPriv(const char *);
};

#pragma GCC visibility pop
