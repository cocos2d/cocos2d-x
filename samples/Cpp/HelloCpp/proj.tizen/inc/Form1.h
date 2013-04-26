//
// Tizen C++ SDK
// Copyright (c) 2012-2013 Samsung Electronics Co., Ltd.
//
// Licensed under the Flora License, Version 1.0 (the License);
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://floralicense.org/license/
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an AS IS BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

#ifndef _FORM1_H_
#define _FORM1_H_

#include <FBase.h>
#include <FUi.h>
#include "HelloCpp.h"


class Form1
	: public Tizen::Ui::Controls::Form
{
public:
	Form1(HelloCpp* pApp): __pApp(pApp)
	{
	}

	virtual ~Form1(void)
	{
	}

	virtual result OnDraw(void)
	{
		if (__pApp != null)
		{
			__pApp->Draw();
		}
		return E_SUCCESS;
	}

private:
	HelloCpp* __pApp;
};

#endif	// _FORM1_H_
