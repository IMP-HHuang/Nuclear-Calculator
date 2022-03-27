#include "gui.h"

#include <iostream>
#include <string.h>
//#include <cstdio>
//#include <fstream>
//#include <cstdlib>
//#include <string>
//#include <cstring>
//#include <sstream>


ClassImp(gui);

//gui::gui() : TGMainFrame()
gui::gui(const TGWindow * p)
{
	MainFrame();
}

gui::~gui()
{}

void gui::MainFrame()
{
	SetCleanup(kDeepCleanup);
	SetBackgroundColor(TColor::RGB2Pixel(62, 62, 62));
	CreateMenuBar();
	ControlPanel(this);
	SetWindowName("Nuclear Calculator");
	MapSubwindows();
	MapWindow();
	Resize(INITIAL_WIDTH, INITIAL_HIGHT);
}
void gui::CreateMenuBar(void)
{
	TGMenuBar *MenuBar = new TGMenuBar(this, INITIAL_WIDTH, 24, kHorizontalFrame);
	AddFrame(MenuBar, new TGLayoutHints(kLHintsTop | kLHintsLeft | kLHintsExpandX, 0, 0, 0, 0));

	MenuFile = new TGPopupMenu(fClient->GetRoot());
	MenuFile->AddEntry("&Exit", FILE_EXIT,0,gClient->GetPicture("bld_exit.png"));
	MenuFile->Associate(this);
	MenuFile->SetBackgroundColor(TColor::RGB2Pixel(0,128,0));
	MenuBar->AddPopup(" &File  ", MenuFile, new TGLayoutHints(kLHintsTop | kLHintsLeft, 0, 0, 0, 0));

	MenuCalculator = new TGPopupMenu(fClient->GetRoot());
	MenuCalculator->AddEntry("Mass", MASS);
//	MenuCalculator->AddSeparator();
	MenuCalculator->AddEntry("Binding Energy ", BINDINGENERGY);
	MenuCalculator->AddEntry("Sp", SP);
	MenuCalculator->AddEntry("Sn", SN);
	MenuCalculator->AddEntry("Q(alpha) ", QALPHA);
	MenuCalculator->AddEntry("Q(Fusion) ", QFUSION);
	MenuCalculator->AddEntry("Vc ", Vc);
	MenuCalculator->Associate(this);
	MenuCalculator->SetBackgroundColor(TColor::RGB2Pixel(0,128,0));
	MenuBar->AddPopup(" &Calculator  ", MenuCalculator, new TGLayoutHints(kLHintsTop | kLHintsLeft, 0, 0, 0, 0));

	MenuSystemicsGraphSp = new TGPopupMenu(fClient->GetRoot());
	MenuSystemicsGraphSp->AddEntry("Isotope", SP_ISOTOPE);
	MenuSystemicsGraphSp->AddEntry("Isotone", SP_ISOTONE);

	MenuSystemicsGraphSn = new TGPopupMenu(fClient->GetRoot());
	MenuSystemicsGraphSn->AddEntry("Isotope", SN_ISOTOPE);
	MenuSystemicsGraphSn->AddEntry("Isotone", SN_ISOTONE);

	MenuSystemicsGraph = new TGPopupMenu(fClient->GetRoot());
	MenuSystemicsGraph->AddPopup("Sp", MenuSystemicsGraphSp);
	MenuSystemicsGraph->AddPopup("Sn", MenuSystemicsGraphSn);
	MenuSystemicsGraph->Associate(this);
	MenuSystemicsGraph->SetBackgroundColor(TColor::RGB2Pixel(0,128,0));
	MenuBar->AddPopup(" &Systemics ", MenuSystemicsGraph, new TGLayoutHints(kLHintsTop | kLHintsLeft, 0, 0, 0, 0));
	

	MenuHIVAP = new TGPopupMenu(fClient->GetRoot());
	MenuHIVAP->AddEntry("Calculate", HIVAPCALCULATE);
	MenuHIVAP->AddEntry("Find Parameters", HIVAPPARAMETER);
	MenuHIVAP->Associate(this);
	MenuBar->AddPopup(" &HIVAP ", MenuHIVAP, new TGLayoutHints(kLHintsTop | kLHintsLeft, 0, 0, 0, 0));

	MenuAlphaDecay = new TGPopupMenu(fClient->GetRoot());
	MenuAlphaDecay->AddEntry("Reduced decay Width", ALPHAREDUCEDWIDTH);

	MenuGammaDecay = new TGPopupMenu(fClient->GetRoot());
	MenuGammaDecay->AddEntry("Weisskopf Estimation", GAMMADECAYRATE);

	MenuDecay = new TGPopupMenu(fClient->GetRoot());
	MenuDecay->AddPopup("Alpha Decay", MenuAlphaDecay);
	MenuDecay->AddPopup("Gamma Decay", MenuGammaDecay);
	MenuDecay->Associate(this);
	MenuDecay->SetBackgroundColor(TColor::RGB2Pixel(0,128,0));
	MenuBar->AddPopup(" &Decay ", MenuDecay, new TGLayoutHints(kLHintsTop | kLHintsLeft, 0, 0, 0, 0));
}
Bool_t gui::ProcessMessage(Long_t msg, Long_t parm1, Long_t parm2)
{
	int test1 = 0, test2 = 0;
	switch (test1 = GET_MSG(msg))
	{
		case  kC_HSLIDER:
			switch (test2 = GET_SUBMSG(msg))
			{
				case  kSL_POS:
					switch(parm1);
					{}
					break;
				default:
					break;
			}
			break;
		case kC_COMMAND:
			switch (test2 = GET_SUBMSG(msg))
			{
				case kCM_MENU:
					switch (parm1)
					{
						case FILE_EXIT:
							CloseWindow();
							break;
						case MASS:
							Mass = new mass(fClient->GetRoot(),this,(char*)"Mass");
							break;
						case BINDINGENERGY:
							BindingEnergy = new bindingenergy(fClient->GetRoot(),this,(char*)"Binding Energy");;
							break;
						case SP:
							SProton = new sp(fClient->GetRoot(),this,(char*)"Sp");;
							break;
						case SN:
							SNutron = new sn(fClient->GetRoot(),this,(char*)"Sn");;
							break;
						case QALPHA:
							QAlpha = new qalpha(fClient->GetRoot(),this,(char*)"Q(alpha)");
							break;
						case QFUSION:
							QFusion = new Qfusion(fClient->GetRoot(),this,(char*)"Q(Fusion)");
							break;
						case Vc:
							test();
							break;
						case SP_ISOTOPE:
							Sp_Isotope_Draw = new draw(fClient->GetRoot(), this, (char*)"Sp(isotope)", "ISOTOPE", "Sp");
							break;
						case SP_ISOTONE:
							Sp_Isotone_Draw = new draw(fClient->GetRoot(),this,(char*)"Sp(isotone)", "ISOTONE", "Sp");
							break;
						case SN_ISOTOPE:
							Sn_Isotope_Draw = new draw(fClient->GetRoot(), this, (char*)"Sn(isotope)", "ISOTOPE", "Sn");
							break;
						case SN_ISOTONE:
							Sn_Isotone_Draw = new draw(fClient->GetRoot(),this,(char*)"Sp(isotone)", "ISOTONE", "Sn");
							break;
						case HIVAPCALCULATE:
							HivapCalculate = new hivap(fClient->GetRoot(),this,(char*)"Calculate");
							break;
						case HIVAPPARAMETER:
							HivapParameter = new hivapParameter(fClient->GetRoot(),this,(char*)"Find Parameter");
							test();
							break;
						case ALPHAREDUCEDWIDTH:
								AlphaDecayReducedWidth = new alphadecayreducedwidth(fClient->GetRoot(),this,(char*)"Alpha Decay");
							break;
						case GAMMADECAYRATE:
								test();
							break;
						default:
							break;
					}
				case kCM_BUTTON:
					switch (parm1)
					{
						default:
							break;
					}
				default:
					break;
			}
		case kC_TEXTENTRY:
			switch (parm1)
			{
				default:
					break;
			}
		default:
				break;
	}
	return kTRUE;
}

void gui::ControlPanel(TGCompositeFrame *TabPanel)
{
	// Image 
	TabPanel->SetBackgroundColor(TColor::RGB2Pixel(62, 62, 62));
	TGGroupFrame *chartframe = new TGGroupFrame(TabPanel,"");
	TabPanel->AddFrame(chartframe,new TGLayoutHints(kLHintsExpandX|kLHintsTop,INITIAL_SIDE_WIDTH,INITIAL_SIDE_WIDTH,0, 0));
	chartframe->SetBackgroundColor(TColor::RGB2Pixel(62, 62, 62));
	TGCompositeFrame *LogoFrame = new TGCompositeFrame(chartframe, 0, 0, kHorizontalFrame);
	chartframe->AddFrame(LogoFrame, new TGLayoutHints(kLHintsTop | kLHintsLeft, 0, 0, 10, 10));
	LogoFrame->SetBackgroundColor(TColor::RGB2Pixel(62, 62, 62));
	TGImageMap* fImage = new TGImageMap(LogoFrame, "chart.jpg");
	LogoFrame->AddFrame(fImage,new TGLayoutHints(kLHintsLeft | kLHintsTop, 0, 0, 0, 0));
	fImage->ChangeOptions(fImage->GetOptions() ^ kRaisedFrame);
	fImage->Resize(720,516);
	fImage->ChangeOptions(fImage->GetOptions() | kFixedSize);

}

void gui::test()
{
	std::cout << "Have not been exploited!" << std::endl;
}
void gui::calculator(Int_t id)
{
	std::cout << Form("Hello GUI %d !", id) << std::endl;
}

void gui::EventInfo(Int_t event, Int_t px, Int_t py, TObject *selected)
{
	const char *text;
	text = selected->GetObjectInfo(px, py);
	std::string str = text;
	std::string xx;
	std::size_t foundx;
	foundx = str.find("x");
	std::size_t foundy;
	foundy = str.find("y");
	string tmp;
	/*
	if (foundx != string::npos && foundy != string::npos)
	{
		tmp = str.substr(str.begin()  + foundx,  str.begin() + foundy);
	}
	*/
//	std::cout << tmp <<std::endl;
}
