//draw.h
#pragma once
#ifndef ALPHADECAYREDUCEDWIDTH_H
#define ALPHADECAYREDUCEDWIDTH_H

#include "TGWindow.h"
#include "TGFrame.h"
#include "TGTextEntry.h"
#include "TGNumberEntry.h"
#include "TGText.h"
#include "TRootEmbeddedCanvas.h"
#include "TGProgressBar.h"
#include "TMath.h"
#include "TF1.h"


#include "nuclear_data.h"

class alphadecayreducedwidth  : public TGTransientFrame
{
	public:
		alphadecayreducedwidth(const TGWindow * p, const TGWindow * main, char *name);
		virtual ~alphadecayreducedwidth();
		Bool_t ProcessMessage(Long_t msg,Long_t parm1,Long_t parm2);
		/*
		Double_t Vn(Double_t *x, Double_t *Massnum);		// MeV
		Double_t Vc(Double_t *x, Double_t *Chargenum);	// MeV
		Double_t Vcent(Double_t *x, Double_t *par);		// MeV
		Double_t Vtot(Double_t *x, Double_t *par);		// MeV
		Double_t Func(double_t *x, double_t *par);
		*/
		void Calculate();
		void HF();
	private:


		TGVerticalFrame* ThisFrame;
		TGHorizontalFrame* NuclearFrame;
		TGTextEntry *NuclearText;
		TGTextEntry *NuclearZText;
		TGNumberEntry *NuclearZNumber;
		TGTextEntry *NuclearAText;
		TGNumberEntry *NuclearANumber;
		TGTextEntry *NuclearNText;
		TGNumberEntry *NuclearNNumber;

		
		TGHorizontalFrame* CalculateFrame;

		TGVerticalFrame* ParameterFrame;
		TGHorizontalFrame* DeltaLFrame;
		TGTextEntry *DeltaLText;
		TGNumberEntry *DeltaLNumber;
		TGHorizontalFrame* EnergyFrame;
		TGTextEntry *EnergyText;
		TGNumberEntry *EnergyNumber;
		TGHorizontalFrame* HalfLifeFrame;
		TGTextEntry *HalfLifeText;
		TGNumberEntry *HalfLifeNumber;
		TGHorizontalFrame* HalfLifeErrorPosFrame;
		TGTextEntry *HalfLifeErrorPosText;
		TGNumberEntry *HalfLifeErrorPosNumber;
		TGHorizontalFrame* HalfLifeErrorNegFrame;
		TGTextEntry *HalfLifeErrorNegText;
		TGNumberEntry *HalfLifeErrorNegNumber;
		TGHorizontalFrame* RatioFrame;
		TGTextEntry *RatioText;
		TGNumberEntry *RatioNumber;
		TGHorizontalFrame* ErrorFrame;
		TGTextEntry *ErrorText;
		TGNumberEntry *ErrorNumber;
		TGHorizontalFrame* CalculateButtonFrame;
		TGTextButton *CalculateB;

		TGHorizontalFrame* QalphaFrame;
		TGTextEntry *QalphaText;
		TGNumberEntry *QalphaNumber;
		TGHorizontalFrame* EtotFrame;
		TGTextEntry *EtotText;
		TGNumberEntry *EtotNumber;
		TGHorizontalFrame* IntegrationFrame;
		TGTextEntry *IntegrationText;
		TGNumberEntry *IntegrationNumber;
		TGHorizontalFrame* PenetrationFrame;
		TGTextEntry *PenetrationText;
		TGNumberEntry *PenetrationNumber;


		TGHorizontalFrame* RDWFrame;
		TGTextEntry *RDWText;
		TGNumberEntry *RDWNumber;

		TGVerticalFrame* CanvasFrame;
		TRootEmbeddedCanvas *FrameCanvas;

		Double_t Delta2 = 0.0;
		Double_t Delta2err = 0.0;

		enum Commands {CalculateButton, HFButton};



};
#endif
