//bindingenergy.h
#pragma once
#ifndef BINDINGENERGY_H
#define BINDINGENERGY_H

#include "TGWindow.h"
#include "TGFrame.h"
#include "TGTextEntry.h"
#include "TGNumberEntry.h"
#include "TGText.h"
#include "TRootEmbeddedCanvas.h"

#include "nuclear_data.h"

class bindingenergy : public TGTransientFrame
{
	public:
		bindingenergy(const TGWindow * p, const TGWindow * main, char *name);
		virtual ~bindingenergy();
		Bool_t ProcessMessage(Long_t msg,Long_t parm1,Long_t parm2);
		void SetNNumber();
		void SetANumber();
	private:
		TGVerticalFrame* MassFrame;
		TGHorizontalFrame* ZANFrame;
		TGTextEntry *ZText;
		TGTextEntry *AText;
		TGTextEntry *NText;
		TGNumberEntry *ZNumber;
		TGNumberEntry *NNumber;
		TGNumberEntry *ANumber;
		TGTextButton *CalculateB;
		TGHorizontalFrame *NuclearFrame;
		TGVerticalFrame* NuclearAZFrame;
		TGHorizontalFrame *NuclearAFrame;
		TGHorizontalFrame *NuclearZFrame;
		TGVerticalFrame* NuclearNameFrame;
		TGVerticalFrame* NuclearNNFrame;
		TGHorizontalFrame *NuclearN1Frame;
		TGHorizontalFrame *NuclearN2Frame;
		TGTextEntry *NuclearAText;
		TGTextEntry *NuclearZText;
		TGTextEntry *NuclearNameText;
		TGTextEntry *NuclearNText;
		TGHorizontalFrame *ResultFrame;
		TGVerticalFrame *ResultValueFrame;
		TGTextEntry *ResultValueText;

		enum Commands {CalculateButton};
		nuclear_data *Nuclear_data;
};
#endif
