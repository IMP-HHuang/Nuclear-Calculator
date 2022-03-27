
#pragma once
#include "TGButton.h"
#include "TGMenu.h"
#include "TColor.h"
#include "TGImageMap.h"
//#include "TGButtonGroup.h"
//#include "TGLabel.h"
//#include "TGNumberEntry.h"
//#include "TGTextViewStream.h"
//#include "TApplication.h"
#include "TGFrame.h"
//#include "TGFileDialog.h"
//#include "TRootEmbeddedCanvas.h"
#include "TGComboBox.h"

//#include "TSystem.h"
//#include "TFile.h"
//#include "TGraph.h"
//#include "TF1.h"
//#include "TH1.h"
//#include "TH2.h"
//#include "TCanvas.h"
//#include "TString.h"
//#include "TRandom.h"

//#include <iostream>
//#include <sstream>
//#include <cstring>

#include "nuclear_data.h"


#include "mass.h"
#include "bindingenergy.h"
#include "sp.h"
#include "sn.h"
#include "qalpha.h"
#include "Qfusion.h"
#include "draw.h"
#include "hivap.h"
#include "hivapParameter.h"
#include "alphadecayreducedwidth.h"

#define INITIAL_SIDE_WIDTH 0
#define INITIAL_CONTANT_WIDTH 760
#define INITIAL_HIGHT 560
#define INITIAL_WIDTH (INITIAL_CONTANT_WIDTH+2*INITIAL_SIDE_WIDTH)

enum Commands
{
	FILE_EXIT, MASS, BINDINGENERGY, SP, SN, QALPHA, QFUSION, Vc, SP_ISOTOPE, SP_ISOTONE, SN_ISOTOPE, SN_ISOTONE, HIVAPCALCULATE, HIVAPPARAMETER, ALPHAREDUCEDWIDTH, GAMMADECAYRATE
};


class gui : public TGMainFrame  //#include "TGFrame.h"
{
	public:
		gui(const TGWindow * p);
		virtual ~gui();
		void test();
		void calculator(Int_t id);
		void EventInfo(Int_t event, Int_t px, Int_t py, TObject *selected);
	private:
		void MainFrame();
		void CreateMenuBar(void);
		void ControlPanel(TGCompositeFrame *TabPanel);
		virtual Bool_t ProcessMessage(Long_t msg, Long_t parm1, Long_t);

		TGPopupMenu *MenuFile;
		TGPopupMenu *MenuCalculator;
		TGPopupMenu *MenuSystemicsGraph;
		TGPopupMenu *MenuSystemicsGraphSp;
		TGPopupMenu *MenuSystemicsGraphSn;
		TGPopupMenu *MenuHIVAP;
		TGPopupMenu *MenuAlphaDecay;
		TGPopupMenu *MenuGammaDecay;
		TGPopupMenu *MenuDecay;

		mass *Mass;
		bindingenergy *BindingEnergy;
		sp *SProton;
		sn *SNutron;
		qalpha *QAlpha;
		Qfusion *QFusion;
		draw *Sp_Isotope_Draw;
		draw *Sp_Isotone_Draw;
		draw *Sn_Isotope_Draw;
		draw *Sn_Isotone_Draw;
		hivap *HivapCalculate;
		hivapParameter *HivapParameter;
		alphadecayreducedwidth *AlphaDecayReducedWidth;
};
