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
#include <UIKit/UISwipeGestureRecognizer.h>
#include <UIKit/UITouch.h>
#define super UIGestureRecognizer
UISwipeGestureRecognizer*
	UISwipeGestureRecognizer::initWithTarget_action(NSActionTarget* ctarget,SEL_PP cselector)
{
	if( super::init())
	{
		self->m_pListener = ctarget;
		self->m_pSelector = cselector;
		self->threshold = 20;
		self->numberOfTouchesRequired = 1;
	}
	return self;
}
void
	UISwipeGestureRecognizer::touchesBegan_withEvent(NSSet* touches ,UIEvent* events)
{
		self->state = UIGestureRecognizerStatePossible;
		if(dependenceCheck())
		{
			UITouch* anyTouch = (UITouch*) touches->anyObject();	
			self->touchesSource = anyTouch->gettouchSource();
			if(touches->count() >= self->numberOfTouchesRequired)
			{
				self->gestureStartPoint = anyTouch->locationInView();
			}else{
				self->state = UIGestureRecognizerStateFailed;
			}
		}
}
void
	UISwipeGestureRecognizer::touchesMoved_withEvent(NSSet* touches ,UIEvent* events)
{
}
void
	UISwipeGestureRecognizer::touchesEnded_withEvent(NSSet* touches ,UIEvent* events)
{
	if(super::dependenceCheck())
	{
	if(self->state == UIGestureRecognizerStatePossible)
	{
		self->state = UIGestureRecognizerStateRecognized;
		UITouch* touch = (UITouch*) touches->anyObject();
		self->direction =  directionFrom_to(self->gestureStartPoint , touch->locationInView());
		(m_pListener->*m_pSelector)(m_pListener ,self);
	}
	}
}
UISwipeGestureRecognizerDirection
	UISwipeGestureRecognizer::directionFrom_to(CGPoint pa ,CGPoint pb)
{
	UISwipeGestureRecognizerDirection pending = UISwipeGestureRecognizerDirectionZero ;
	BOOL first = YES;
	if((pb.x - pa.x) > threshold )
		pending = (UISwipeGestureRecognizerDirection)( pending |  UISwipeGestureRecognizerDirectionRight);
	if((pb.x - pa.x) < -threshold  )
		pending = (UISwipeGestureRecognizerDirection)( pending |  UISwipeGestureRecognizerDirectionLeft);
	if((pb.y - pa.y) > threshold )
		pending = (UISwipeGestureRecognizerDirection)( pending |  UISwipeGestureRecognizerDirectionUp);
	if((pb.y - pa.y) < -threshold )
		pending = (UISwipeGestureRecognizerDirection)( pending |  UISwipeGestureRecognizerDirectionDown);
	return pending;
}
void
	UISwipeGestureRecognizer::dealloc(){}