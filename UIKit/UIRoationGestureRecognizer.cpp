/****************************************************************************
	Cocos  Project
			hosting	github.com
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
#include <UIKit/UIRotationGestureRecognizer.h>
#include <UIKit/UITouch.h>
#define super UIGestureRecognizer
CIVector* lastOrentaionOfHands;
CGFloat baseRotaion;
UIRotationGestureRecognizer*
	UIRotationGestureRecognizer::initWithTarget_action(NSActionTarget* ctarget,SEL_PP cselector)
{
	if(super::init())
	{
	self->m_pListener = ctarget;
	self->m_pSelector = cselector;
	self->deltaRotation = 0;
	self->touchMovedEventCount = 0;
	lastOrentaionOfHands = nil;
	}
	return self;
}
void
	UIRotationGestureRecognizer::touchesBegan_withEvent(NSSet* touches ,UIEvent* events)
{
		self->state = UIGestureRecognizerStatePossible;
		if(super::dependenceCheck())
		{
			self->state = UIGestureRecognizeStateBegan;
			bool fistTouch = true;
			CGPoint touchLoaction;
			nfor(UITouch* ,touch ,touches)
				if(fistTouch)
				{
					touchLoaction = touch->getlocation();
					fistTouch= false;
				}else{
					self->gestureStartOrentaion = CIVector::vectorFrom_to( touch->getlocation() ,touchLoaction);
			}
			nend
		if(lastOrentaionOfHands)
			baseRotaion = CGAngleMake ( self->gestureStartOrentaion ,lastOrentaionOfHands );
		}
}
void
	UIRotationGestureRecognizer::touchesMoved_withEvent(NSSet* touches ,UIEvent* events)
{
	if(self->state != UIGestureRecognizeStateBegan && self->state != UIGestureRecognizeStateChanged)
	{
		return;
	}
	self->state = UIGestureRecognizeStateChanged;
	bool fistTouch = true;
	CGPoint touchLoaction;
	nfor(UITouch* ,touch ,touches)
		if(fistTouch)
	 	{
			touchLoaction = touch->getlocation();
			fistTouch= false;
		}else{
			CIVector* newVector = CIVector::vectorFrom_to( touch->getlocation() , touchLoaction);
			CGFloat newRotation = CGRadianMake ( self->gestureStartOrentaion ,newVector);
			if(lastOrentaionOfHands == nil)
			{
				self->rotation = newRotation * 0.25f;
			}else{
				self->rotation = (newRotation * 0.25f + baseRotaion) ;
			}
			newVector->release();
		}
	nend
	(m_pListener->*m_pSelector)(nil,self);
}
void
	UIRotationGestureRecognizer::touchesEnded_withEvent(NSSet* touches ,UIEvent* events)
{
	if(self->state == UIGestureRecognizeStateChanged)
	{
		self->state = UIGestureRecognizeStateEnded;
		bool fistTouch = true;
		CGPoint touchLoaction;
		nfor(UITouch* ,touch ,touches)
			if(fistTouch)
			{
				touchLoaction = touch->getlocation();
				fistTouch= false;
			}else{
				lastOrentaionOfHands = CIVector::vectorFrom_to(touch->getlocation(),touchLoaction);
			}
		nend
	}
}
void
	UIRotationGestureRecognizer::dealloc(){}