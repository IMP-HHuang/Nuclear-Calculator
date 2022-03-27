//draw.h
#pragma once
#ifndef DRAW_H
#define DRAW_H

#include "TGWindow.h"
#include "TGFrame.h"
#include "TGTextEntry.h"
#include "TGNumberEntry.h"
#include "TGText.h"
#include "TRootEmbeddedCanvas.h"

#include "nuclear_data.h"

class draw : public TGTransientFrame
{
	public:
		draw(const TGWindow * p, const TGWindow * main, char *name, TString Draw_Option_In, TString Draw_Option_Spn_In);
		virtual ~draw();
		Bool_t ProcessMessage(Long_t msg,Long_t parm1,Long_t parm2);
	private:
		TString Draw_Option;
		TString Draw_Option_Spn;
		TGVerticalFrame* Sp_DrawFrame;
		TGHorizontalFrame* ZANFrame;
		TGTextEntry *ZminText;
		TGTextEntry *ZmaxText;
		TGTextEntry *NminText;
		TGTextEntry *NmaxText;
		TGNumberEntry *ZminNumber;
		TGNumberEntry *ZmaxNumber;
		TGNumberEntry *NminNumber;
		TGNumberEntry *NmaxNumber;
		TGVerticalFrame* ZEvenOddFrame;
		TGCheckButton* ZEvenCheckButton;
		TGCheckButton* ZOddCheckButton;
		TGVerticalFrame* NEvenOddFrame;
		TGCheckButton* NEvenCheckButton;
		TGCheckButton* NOddCheckButton;
		TGTextButton *DrawB;
		TRootEmbeddedCanvas *FrameCanvas;

		enum Commands {DrawButton};
};
#endif
