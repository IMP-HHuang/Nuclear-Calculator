//draw.h
#pragma once
#ifndef HIVAPPARAMETER_H
#define HIVAPPARAMETER_H

#include "TGWindow.h"
#include "TGFrame.h"
#include "TGTextEntry.h"
#include "TGNumberEntry.h"
#include "TGText.h"
#include "TRootEmbeddedCanvas.h"
#include "TGProgressBar.h"


#include "nuclear_data.h"

typedef struct CROSSSECTIONEXP{
	Int_t ZFER;
	Int_t AFER;
	TString Channel;
	Int_t Zp;
	Int_t Ap;
	Int_t Zt;
	Int_t At;
	Double_t BeamEnergy;
	Double_t CrossSectionub;
	Double_t ErrCrossSectionub;
	TString Facility;
	Double_t Cf;
	Double_t Af_An;
	Double_t CrossSectionubCal;
}CrossSectionExp;

class hivapParameter  : public TGTransientFrame
{
	public:
		hivapParameter(const TGWindow * p, const TGWindow * main, char *name);
		virtual ~hivapParameter();
		Bool_t ProcessMessage(Long_t msg,Long_t parm1,Long_t parm2);
	private:

		void MakeHivapInputfile(Int_t ZpIn, Int_t ApIn, Int_t ZtIn, Int_t AtIn, Double_t BeamEnergy, Double_t Af_AnIn, Double_t CfIn);
		Double_t ReadCalCulatedCrossSection(Int_t ZpIn, Int_t ApIn, Int_t ZtIn, Int_t AtIn, Int_t ZFERIn, Int_t AFERIn);
		void Draw();

		Int_t EvaporationProtonNumber = 5;
		Int_t EvaporationNeutronNumber = 11;

		TGVerticalFrame* HivapParameterFrame;
		TGHorizontalFrame* FusionFrame;
		TGVerticalFrame* FusionNameFrame;
		TGTextEntry *FusionNameText;
		TGVerticalFrame* FusionInformationFrame;
		TGHorizontalFrame* FusionMinFrame;
		TGTextEntry *FusionMinZText;
		TGNumberEntry *FusionMinZNumber;
		TGTextEntry *FusionMinAText;
		TGNumberEntry *FusionMinANumber;
		TGTextEntry *FusionMinNText;
		TGNumberEntry *FusionMinNNumber;

		TGHorizontalFrame* FusionMaxFrame;
		TGTextEntry *FusionMaxZText;
		TGNumberEntry *FusionMaxZNumber;
		TGTextEntry *FusionMaxAText;
		TGNumberEntry *FusionMaxANumber;
		TGTextEntry *FusionMaxNText;
		TGNumberEntry *FusionMaxNNumber;
		
		TGHorizontalFrame* CalculateFrame;

		TGVerticalFrame* ParameterFrame;
		TGHorizontalFrame* CfMinFrame;
		TGTextEntry *CfMinText;
		TGNumberEntry *CfMinNumber;
		TGHorizontalFrame* CfMaxFrame;
		TGTextEntry *CfMaxText;
		TGNumberEntry *CfMaxNumber;
		TGHorizontalFrame* CfDetFrame;
		TGTextEntry *CfDetText;
		TGNumberEntry *CfDetNumber;
		TGHorizontalFrame* Af_AnMinFrame;
		TGTextEntry *Af_AnMinText;
		TGNumberEntry *Af_AnMinNumber;
		TGHorizontalFrame* Af_AnMaxFrame;
		TGTextEntry *Af_AnMaxText;
		TGNumberEntry *Af_AnMaxNumber;
		TGHorizontalFrame* Af_AnDetFrame;
		TGTextEntry *Af_AnDetText;
		TGNumberEntry *Af_AnDetNumber;
		TGHorizontalFrame* FindButtonFrame;
		TGTextButton *FindB;


		TGVerticalFrame* CanvasFrame;
		TGHorizontalFrame* CfResidualCanvasFrame;
		TGVerticalFrame* CfCanvasFrame;
		TGVerticalFrame* ResidualCanvasFrame;
		TRootEmbeddedCanvas *CfFrameCanvas;
		TRootEmbeddedCanvas *ResidualFrameCanvas;
		TGHorizontalFrame* ProgressBarFram;
		TGHProgressBar* ProgressBar;

		enum Commands {CalculateButton, FindButton};
		Int_t ngraph_Draw = 0;


		std::vector<CrossSectionExp> CrossSectionExpVe;

};
#endif
