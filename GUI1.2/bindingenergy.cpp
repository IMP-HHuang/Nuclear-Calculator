//bindingenergy.cpp

#include "TColor.h"
#include "TLatex.h"
#include "TCanvas.h"
#include "TGSplitter.h"
#include "TG3DLine.h"
#include "bindingenergy.h"
//#include "nuclear_data.h"
#include "iostream"

bindingenergy::bindingenergy(const TGWindow * p, const TGWindow * main, char *name)
{
	SetCleanup(kDeepCleanup);
	SetBackgroundColor(TColor::RGB2Pixel(62, 62, 62));

	MassFrame = new TGVerticalFrame(this, 200, 600);
	AddFrame(MassFrame, new TGLayoutHints(kLHintsTop | kLHintsLeft, 10, 10, 5, 5));
	MassFrame->SetBackgroundColor(TColor::RGB2Pixel(62, 62, 62));
	TGHSplitter *hsplitter0 = new TGHSplitter(MassFrame,200,2);
	MassFrame->AddFrame(hsplitter0, new TGLayoutHints(kLHintsTop | kLHintsExpandX,0,0,10,10));

	ZANFrame = new TGHorizontalFrame(MassFrame, 200, 300);
	MassFrame->AddFrame(ZANFrame, new TGLayoutHints(kLHintsTop | kLHintsLeft, 0, 0, 0, 0));
	ZANFrame->SetBackgroundColor(TColor::RGB2Pixel(62, 62, 62));

	ZText = new TGTextEntry(ZANFrame, new TGTextBuffer(100), 10000);
	ZText->SetText("Z = ");
	ZANFrame->AddFrame(ZText, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 10, 0));
	ZText->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
	ZText->SetAlignment(kTextCenterX);
	ZText->Resize(70, 40);
	ZText->SetEnabled(kFALSE);
	ZText->SetFrameDrawn(kFALSE);
	ZText->ChangeBackground(TColor::RGB2Pixel(62, 62, 62));
	ZText->SetTextColor(TColor::RGB2Pixel(131, 131, 131), false);

	ZNumber = new TGNumberEntry(ZANFrame, 0, 0, TGNumberFormat::kNESInteger);
   	ZNumber->Connect("ValueSet(Long_t)", "bindingenergy", this, "SetANumber()");
   	(ZNumber->GetNumberEntry())->Connect("ReturnPressed()", "bindingenergy", this, "SetANumber()");
	ZANFrame->AddFrame(ZNumber, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
	ZNumber->GetButtonUp()->ChangeOptions(ZNumber->GetButtonUp()->GetOptions() ^ kRaisedFrame);
	ZNumber->GetButtonDown()->ChangeOptions(ZNumber->GetButtonDown()->GetOptions() ^ kRaisedFrame);
	ZNumber->GetNumberEntry()->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
	ZNumber->Resize(70, 40);
	ZNumber->SetNumber(82);
	ZNumber->Associate(this);

	AText = new TGTextEntry(ZANFrame, new TGTextBuffer(100), 10000);
	AText->SetText("A = ");
	ZANFrame->AddFrame(AText, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 10, 0));
	AText->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
	AText->SetAlignment(kTextCenterX);
	AText->Resize(70, 40);
	AText->SetEnabled(kFALSE);
	AText->SetFrameDrawn(kFALSE);
	AText->ChangeBackground(TColor::RGB2Pixel(62, 62, 62));
	AText->SetTextColor(TColor::RGB2Pixel(131, 131, 131), false);
	ANumber = new TGNumberEntry(ZANFrame, 0, 0, TGNumberFormat::kNESInteger);
  	ANumber->Connect("ValueSet(Long_t)", "bindingenergy", this, "SetNNumber()");
   	(ANumber->GetNumberEntry())->Connect("ReturnPressed()", "bindingenergy", this, "SetNNumber()");
	ZANFrame->AddFrame(ANumber, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
	ANumber->GetButtonUp()->ChangeOptions(ZNumber->GetButtonUp()->GetOptions() ^ kRaisedFrame);
	ANumber->GetButtonDown()->ChangeOptions(ZNumber->GetButtonDown()->GetOptions() ^ kRaisedFrame);
	ANumber->GetNumberEntry()->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
	ANumber->Resize(70, 40);
	ANumber->SetNumber(208);
	ANumber->Associate(this);

	NText = new TGTextEntry(ZANFrame, new TGTextBuffer(100), 10000);
	NText->SetText("N = ");
	ZANFrame->AddFrame(NText, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 10, 0));
	NText->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
	NText->SetAlignment(kTextCenterX);
	NText->Resize(70, 40);
	NText->SetEnabled(kFALSE);
	NText->SetFrameDrawn(kFALSE);
	NText->ChangeBackground(TColor::RGB2Pixel(62, 62, 62));
	NText->SetTextColor(TColor::RGB2Pixel(131, 131, 131), false);
	NNumber = new TGNumberEntry(ZANFrame, 0, 0, TGNumberFormat::kNESInteger);
   	NNumber->Connect("ValueSet(Long_t)", "bindingenergy", this, "SetANumber()");
   	(NNumber->GetNumberEntry())->Connect("ReturnPressed()", "bindingenergy", this, "SetANumber()");
	ZANFrame->AddFrame(NNumber, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
	NNumber->GetButtonUp()->ChangeOptions(ZNumber->GetButtonUp()->GetOptions() ^ kRaisedFrame);
	NNumber->GetButtonDown()->ChangeOptions(ZNumber->GetButtonDown()->GetOptions() ^ kRaisedFrame);
	NNumber->GetNumberEntry()->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
	NNumber->Resize(70, 40);
	NNumber->SetNumber(126);
	NNumber->Associate(this);
	CalculateB = new TGTextButton(MassFrame, "  Calculator  ", CalculateButton);
	MassFrame->AddFrame(CalculateB, new TGLayoutHints(kLHintsCenterX, 0, 0, 10, 10));
	CalculateB->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
	CalculateB->Resize(70, 100);
	CalculateB->SetTextColor(TColor::RGB2Pixel(255, 255, 255));
	CalculateB->SetBackgroundColor(TColor::RGB2Pixel(34, 151, 159));
	CalculateB->Associate(this);

	TGHSplitter *hsplitter1 = new TGHSplitter(MassFrame,200,2);
	MassFrame->AddFrame(hsplitter1, new TGLayoutHints(kLHintsTop | kLHintsExpandX,0,0,10,10));
	hsplitter1->SetBackgroundColor(TColor::RGB2Pixel(0,0,0));
	NuclearFrame = new TGHorizontalFrame(MassFrame, 200, 600);
	MassFrame->AddFrame(NuclearFrame, new TGLayoutHints(kLHintsCenterX, 0, 0, 10, 0));
	NuclearFrame->SetBackgroundColor(TColor::RGB2Pixel(62, 62, 62));
	NuclearAZFrame = new TGVerticalFrame(NuclearFrame, 75, 600);
	NuclearAZFrame->SetBackgroundColor(TColor::RGB2Pixel(62, 62, 62));
	NuclearFrame->AddFrame(NuclearAZFrame, new TGLayoutHints(kLHintsCenterX, 0, 0, 10, 0));
	NuclearAFrame= new TGHorizontalFrame(NuclearAZFrame, 75, 300);
	NuclearAFrame->SetBackgroundColor(TColor::RGB2Pixel(62, 62, 62));
	NuclearAZFrame->AddFrame(NuclearAFrame, new TGLayoutHints(kLHintsCenterX, 0, 0, 10, 0));
	NuclearAText = new TGTextEntry(NuclearAFrame, new TGTextBuffer(100), 10000);
	NuclearAText->SetText("208");
	NuclearAFrame->AddFrame(NuclearAText, new TGLayoutHints(kLHintsCenterX, 0, 0, 10, 0));
	NuclearAText->SetFont("-adobe-helvetica-bold-r-*-*-40-*-*-*-*-*-iso8859-1", true);
	NuclearAText->SetAlignment(kTextCenterX);
	NuclearAText->Resize(185, 40);
	NuclearAText->SetEnabled(kFALSE);
	NuclearAText->SetFrameDrawn(kFALSE);
	NuclearAText->ChangeBackground(TColor::RGB2Pixel(62, 62, 62));
	NuclearAText->SetTextColor(TColor::RGB2Pixel(131, 131, 131), false);
	NuclearAText->SetAlignment(kTextRight);
	NuclearZFrame= new TGHorizontalFrame(NuclearAZFrame, 75, 300);
	NuclearZFrame->SetBackgroundColor(TColor::RGB2Pixel(62, 62, 62));
	NuclearAZFrame->AddFrame(NuclearZFrame, new TGLayoutHints(kLHintsCenterX, 0, 0, 10, 0));
	NuclearZText = new TGTextEntry(NuclearZFrame, new TGTextBuffer(100), 10000);
	NuclearZText->SetText("82");
	NuclearZFrame->AddFrame(NuclearZText, new TGLayoutHints(kLHintsCenterX, 0, 0, 10, 0));
	NuclearZText->SetFont("-adobe-helvetica-bold-r-*-*-40-*-*-*-*-*-iso8859-1", true);
	NuclearZText->SetAlignment(kTextCenterX);
	NuclearZText->Resize(185, 40);
	NuclearZText->SetEnabled(kFALSE);
	NuclearZText->SetFrameDrawn(kFALSE);
	NuclearZText->ChangeBackground(TColor::RGB2Pixel(62, 62, 62));
	NuclearZText->SetTextColor(TColor::RGB2Pixel(131, 131, 131), false);
	NuclearZText->SetAlignment(kTextRight);
	NuclearNameFrame = new TGVerticalFrame(NuclearFrame, 75, 600);
	NuclearNameFrame->SetBackgroundColor(TColor::RGB2Pixel(62, 62, 62));
	NuclearFrame->AddFrame(NuclearNameFrame, new TGLayoutHints(kLHintsCenterX, 0, 0, 10, 0));
	NuclearNameText = new TGTextEntry(NuclearNameFrame, new TGTextBuffer(100), 10000);
	NuclearNameText->SetText("Pb");
	NuclearNameFrame->AddFrame(NuclearNameText, new TGLayoutHints(kLHintsCenterX, 0, 0, 10, 0));
	NuclearNameText->SetFont("-adobe-helvetica-bold-r-*-*-40-*-*-*-*-*-iso8859-1", true);
	NuclearNameText->SetAlignment(kTextCenterX);
	NuclearNameText->Resize(50, 120);
	NuclearNameText->SetEnabled(kFALSE);
	NuclearNameText->SetFrameDrawn(kFALSE);
	NuclearNameText->ChangeBackground(TColor::RGB2Pixel(62, 62, 62));
	NuclearNameText->SetTextColor(TColor::RGB2Pixel(131, 131, 131), false);
	NuclearNameText->SetAlignment(kTextCenterX);
	NuclearNNFrame = new TGVerticalFrame(NuclearFrame, 75, 600);
	NuclearNNFrame->SetBackgroundColor(TColor::RGB2Pixel(62, 62, 62));
	NuclearFrame->AddFrame(NuclearNNFrame, new TGLayoutHints(kLHintsCenterX, 0, 0, 10, 0));
	NuclearN1Frame= new TGHorizontalFrame(NuclearNNFrame, 75, 300);
	NuclearN1Frame->SetBackgroundColor(TColor::RGB2Pixel(62, 62, 62));
	NuclearNNFrame->AddFrame(NuclearN1Frame, new TGLayoutHints(kLHintsCenterX, 0, 0, 10, 0));
	TGTextEntry *NuclearNtText = new TGTextEntry(NuclearN1Frame, new TGTextBuffer(100), 10000);
	NuclearNtText->SetText("");
	NuclearN1Frame->AddFrame(NuclearNtText, new TGLayoutHints(kLHintsCenterX, 0, 0, 10, 0));
	NuclearNtText->SetFont("-adobe-helvetica-bold-r-*-*-40-*-*-*-*-*-iso8859-1", true);
	NuclearNtText->SetAlignment(kTextCenterX);
	NuclearNtText->Resize(185, 40);
	NuclearNtText->SetEnabled(kFALSE);
	NuclearNtText->SetFrameDrawn(kFALSE);
	NuclearNtText->ChangeBackground(TColor::RGB2Pixel(62, 62, 62));
	NuclearNtText->SetTextColor(TColor::RGB2Pixel(131, 131, 131), false);
	NuclearNtText->SetAlignment(kTextCenterX);

	NuclearN2Frame= new TGHorizontalFrame(NuclearNNFrame, 75, 300);
	NuclearN2Frame->SetBackgroundColor(TColor::RGB2Pixel(62, 62, 62));
	NuclearNNFrame->AddFrame(NuclearN2Frame, new TGLayoutHints(kLHintsCenterX, 0, 0, 10, 0));
	NuclearNText = new TGTextEntry(NuclearN2Frame, new TGTextBuffer(100), 10000);
	NuclearNText->SetText("126");
	NuclearN2Frame->AddFrame(NuclearNText, new TGLayoutHints(kLHintsCenterX, 0, 0, 10, 0));
	NuclearNText->SetFont("-adobe-helvetica-bold-r-*-*-40-*-*-*-*-*-iso8859-1", true);
	NuclearNText->SetAlignment(kTextCenterX);
	NuclearNText->Resize(185, 40);
	NuclearNText->SetEnabled(kFALSE);
	NuclearNText->SetFrameDrawn(kFALSE);
	NuclearNText->ChangeBackground(TColor::RGB2Pixel(62, 62, 62));
	NuclearNText->SetTextColor(TColor::RGB2Pixel(131, 131, 131), false);
	NuclearNText->SetAlignment(kTextLeft);

	TGHSplitter *hsplitter2 = new TGHSplitter(MassFrame,200,2);
	MassFrame->AddFrame(hsplitter2, new TGLayoutHints(kLHintsTop | kLHintsExpandX,0,0,10,10));
	hsplitter2->SetBackgroundColor(TColor::RGB2Pixel(0,0,0));
	ResultFrame = new TGHorizontalFrame(MassFrame, 200, 20);
	ResultFrame->SetBackgroundColor(TColor::RGB2Pixel(62, 62, 62));
	MassFrame->AddFrame(ResultFrame, new TGLayoutHints(kLHintsCenterX, 0, 0, 10, 0));
	ResultValueFrame = new TGVerticalFrame(ResultFrame, 200, 20);
	ResultValueFrame->SetBackgroundColor(TColor::RGB2Pixel(62, 62, 62));
	ResultFrame->AddFrame(ResultValueFrame, new TGLayoutHints(kLHintsCenterX, 0, 0, 10, 10));
	ResultValueText = new TGTextEntry(ResultValueFrame, new TGTextBuffer(200), 10000);
	ResultValueText->SetText("Binding Energy (Error) MeV");
	ResultValueFrame->AddFrame(ResultValueText, new TGLayoutHints(kLHintsCenterX, 0, 0, 10, 10));
	ResultValueText->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", true);
	ResultValueText->Resize(400, 20);
	ResultValueText->SetEnabled(kFALSE);
	ResultValueText->SetFrameDrawn(kFALSE);
	ResultValueText->ChangeBackground(TColor::RGB2Pixel(62, 62, 62));
	ResultValueText->SetTextColor(TColor::RGB2Pixel(131, 131, 131), false);
	ResultValueText->SetAlignment(kTextCenterX);


	MapSubwindows();
	Resize();
	CenterOnParent();
	SetWindowName(name);
	MapWindow();
}
bindingenergy::~bindingenergy(){}

Bool_t bindingenergy::ProcessMessage(Long_t msg,Long_t parm1, Long_t parm2)
{
	switch (GET_MSG(msg))
	{
		case kC_COMMAND:
			switch (GET_SUBMSG(msg))
			{
				case kCM_BUTTON:
					switch (parm1)
					{
						case CalculateButton:
						{
							ResultValueText->SetTextColor(TColor::RGB2Pixel(131, 131, 131));
							NNumber->GetNumberEntry()->SetTextColor(TColor::RGB2Pixel(0, 0, 0));
							if(Int_t(ZNumber->GetNumber())+Int_t(NNumber->GetNumber()) != Int_t(ANumber->GetNumber()))
							{
								NNumber->SetNumber(ANumber->GetNumber()-ZNumber->GetNumber());
								NNumber->GetNumberEntry()->SetTextColor(TColor::RGB2Pixel(255, 0, 0));
							}
								Nuclear_data = new nuclear_data(Int_t(ZNumber->GetNumber()), Int_t(ANumber->GetNumber()), Int_t(NNumber->GetNumber()));
							NuclearAText->SetText(Form("%d", Int_t(ANumber->GetNumber())));
							NuclearZText->SetText(Form("%d", Int_t(ZNumber->GetNumber())));
							NuclearNText->SetText(Form("%d", Int_t(NNumber->GetNumber())));
							NuclearNameText->SetText(TString(Nuclear_data->getname()));
							if(Nuclear_data->getflag())
							{
								Double_t TheResultValue = ZNumber->GetNumber()*938.78320 + NNumber->GetNumber()*939.56555 - Nuclear_data->getmass();
								Double_t TheResultError = Nuclear_data->geterror();
								ResultValueText->SetText(Form("%0.6E(%0.6E) MeV", TheResultValue, TheResultError));
							}
							else if(Nuclear_data->getmass() > 999.0)
							{
								ResultValueText->SetText(Form("%0.6E", 0.0));
								ResultValueText->SetTextColor(TColor::RGB2Pixel(255, 0, 0));
							}
							else
							{
								Double_t TheResultValue = ZNumber->GetNumber()*938.78320 + NNumber->GetNumber()*939.56555 - Nuclear_data->getmass();
								Double_t TheResultError = Nuclear_data->geterror();
								ResultValueText->SetText(Form("%0.6E(%0.6E)# MeV", TheResultValue, TheResultError));
								ResultValueText->SetTextColor(TColor::RGB2Pixel(0, 0, 255));

							}
							delete Nuclear_data;
							break;
						}
						default:
							break;
					}
				default:
					break;
			}
		default:
			break;
	}
	return kTRUE;
}
void bindingenergy::SetNNumber()
{
	NNumber->SetNumber(ANumber->GetNumber() - ZNumber->GetNumber());
}
void bindingenergy::SetANumber()
{
	ANumber->SetNumber(NNumber->GetNumber() + ZNumber->GetNumber());
}
