//draw.h
#pragma once
#ifndef HIVAP_H
#define HIVAP_H

#include "TGWindow.h"
#include "TGFrame.h"
#include "TGTextEntry.h"
#include "TGNumberEntry.h"
#include "TGText.h"
#include "TRootEmbeddedCanvas.h"
#include "TGProgressBar.h"


#include "nuclear_data.h"

class hivap  : public TGTransientFrame
{
	public:
		hivap(const TGWindow * p, const TGWindow * main, char *name);
		virtual ~hivap();
		Bool_t ProcessMessage(Long_t msg,Long_t parm1,Long_t parm2);
	private:

		void MakeHivapInputfile(Double_t Ecm_in);
		void ReadExcitationFunction();
		void Draw();

		TGVerticalFrame* HivapFrame;
		TGHorizontalFrame* ProjectileFrame;
		TGTextEntry *ProjectileText;
		TGTextEntry *ProjectileZText;
		TGNumberEntry *ProjectileZNumber;
		TGTextEntry *ProjectileAText;
		TGNumberEntry *ProjectileANumber;
		TGTextEntry *ProjectileNText;
		TGNumberEntry *ProjectileNNumber;

		TGHorizontalFrame* TargetFrame;
		TGTextEntry *TargetText;
		TGTextEntry *TargetZText;
		TGNumberEntry *TargetZNumber;
		TGTextEntry *TargetAText;
		TGNumberEntry *TargetANumber;
		TGTextEntry *TargetNText;
		TGNumberEntry *TargetNNumber;
		
		TGHorizontalFrame* CalculateFrame;

		TGVerticalFrame* ParameterFrame;
		TGHorizontalFrame* EcmMinFrame;
		TGTextEntry *EcmMinText;
		TGNumberEntry *EcmMinNumber;
		TGHorizontalFrame* EcmMaxFrame;
		TGTextEntry *EcmMaxText;
		TGNumberEntry *EcmMaxNumber;
		TGHorizontalFrame* EcmDetEFrame;
		TGTextEntry *EcmDetEText;
		TGNumberEntry *EcmDetENumber;
		TGHorizontalFrame* CfFrame;
		TGTextEntry *CfText;
		TGNumberEntry *CfNumber;
		TGHorizontalFrame* Af_AnFrame;
		TGTextEntry *Af_AnText;
		TGNumberEntry *Af_AnNumber;
		TGHorizontalFrame* EvaporationProtonFrame;
		TGTextEntry *EvaporationProtonText;
		TGNumberEntry *EvaporationProtonNumber;
		TGHorizontalFrame* EvaporationNeutronFrame;
		TGTextEntry *EvaporationNeutronText;
		TGNumberEntry *EvaporationNeutronNumber;
		TGHorizontalFrame* DrawPminFrame;
		TGTextEntry *DrawPminText;
		TGNumberEntry *DrawPminNumber;
		TGHorizontalFrame* DrawPmaxFrame;
		TGTextEntry *DrawPmaxText;
		TGNumberEntry *DrawPmaxNumber;
		TGHorizontalFrame* DrawAminFrame;
		TGTextEntry *DrawAminText;
		TGNumberEntry *DrawAminNumber;
		TGHorizontalFrame* DrawAmaxFrame;
		TGTextEntry *DrawAmaxText;
		TGNumberEntry *DrawAmaxNumber;
		TGHorizontalFrame* DrawYminFrame;
		TGTextEntry *DrawYminText;
		TGNumberEntry *DrawYminNumber;
		TGHorizontalFrame* DrawYmaxFrame;
		TGTextEntry *DrawYmaxText;
		TGNumberEntry *DrawYmaxNumber;
		TGHorizontalFrame* DrawVBassFrame;
		TGTextEntry *DrawVBassText;
		TGNumberEntry *DrawVBassNumber;

		TGHorizontalFrame* CalculateButtonFrame;
		TGTextButton *CalculateB;
		TGHorizontalFrame* DrawButtonFrame;
		TGTextButton *DrawB;

		TGVerticalFrame* CanvasFrame;
		TRootEmbeddedCanvas *FrameCanvas;
		TGHorizontalFrame* ProgressBarFram;
		TGHProgressBar* ProgressBar;

		enum Commands {CalculateButton, DrawButton};

		Int_t nEnergyHivap;
		Int_t nCrosssectionHivapTmp;
		Int_t nCrosssectionHivap;
		TString* name;
		Double_t HIVAP_Energy_Exp[100];
		Double_t HIVAP_Energy_cm[100];
		Double_t** HIVAP_cross_section;
		Int_t ngraph_Draw;

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
		}CrossSectionExp;
		std::vector<CrossSectionExp> CrossSectionExpVe;

};
#endif
