//draw.cpp

#include "TColor.h"
#include "TLatex.h"
#include "TCanvas.h"
#include "TGSplitter.h"
#include "TG3DLine.h"
#include "TGraphErrors.h"
#include "TMultiGraph.h"
#include "TAxis.h"
#include "TLegend.h"
#include "TArrow.h"

#include <vector>
#include <cstdlib>

#include "alphadecayreducedwidth.h"
#include "iostream"

alphadecayreducedwidth::alphadecayreducedwidth(const TGWindow * p, const TGWindow * main, char *name)
{
	SetCleanup(kDeepCleanup);
	SetBackgroundColor(TColor::RGB2Pixel(62, 62, 62));

	ThisFrame = new TGVerticalFrame(this, 800, 1500);
	AddFrame(ThisFrame, new TGLayoutHints(kLHintsTop | kLHintsLeft, 10, 10, 5, 5));
	ThisFrame->SetBackgroundColor(TColor::RGB2Pixel(62, 62, 62));
	TGHSplitter *hsplitter0 = new TGHSplitter(ThisFrame,200,2);
	ThisFrame->AddFrame(hsplitter0, new TGLayoutHints(kLHintsTop | kLHintsExpandX,0,0,10,10));
	NuclearFrame = new TGHorizontalFrame(ThisFrame, 800, 40);
	ThisFrame->AddFrame(NuclearFrame, new TGLayoutHints(kLHintsTop | kLHintsLeft, 0, 0, 0, 0));
	NuclearFrame->SetBackgroundColor(TColor::RGB2Pixel(62, 62, 62));

	NuclearText = new TGTextEntry(NuclearFrame, new TGTextBuffer(100), 10000);
	NuclearText->SetText("Mother : ");
	NuclearFrame->AddFrame(NuclearText, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
	NuclearText->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
	NuclearText->Resize(150, 40);
	NuclearText->SetEnabled(kFALSE);
	NuclearText->SetFrameDrawn(kFALSE);
	NuclearText->ChangeBackground(TColor::RGB2Pixel(62, 62, 62));
	NuclearText->SetTextColor(TColor::RGB2Pixel(131, 131, 131), false);

	NuclearZText = new TGTextEntry(NuclearFrame, new TGTextBuffer(100), 10000);
	NuclearZText->SetText("Z = ");
	NuclearFrame->AddFrame(NuclearZText, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
	NuclearZText->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
	NuclearZText->SetAlignment(kTextCenterX);
	NuclearZText->Resize(200, 40);
	NuclearZText->SetEnabled(kFALSE);
	NuclearZText->SetFrameDrawn(kFALSE);
	NuclearZText->ChangeBackground(TColor::RGB2Pixel(62, 62, 62));
	NuclearZText->SetTextColor(TColor::RGB2Pixel(131, 131, 131), false);

	NuclearZNumber = new TGNumberEntry(NuclearFrame, 0, 0, TGNumberFormat::kNESInteger);
	NuclearFrame->AddFrame(NuclearZNumber, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
	NuclearZNumber->GetButtonUp()->ChangeOptions(NuclearZNumber->GetButtonUp()->GetOptions() ^ kRaisedFrame);
	NuclearZNumber->GetButtonDown()->ChangeOptions(NuclearZNumber->GetButtonDown()->GetOptions() ^ kRaisedFrame);
	NuclearZNumber->GetNumberEntry()->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
	NuclearZNumber->Resize(100, 40);
	NuclearZNumber->SetNumber(84);
	NuclearZNumber->Associate(this);

	NuclearAText = new TGTextEntry(NuclearFrame, new TGTextBuffer(100), 10000);
	NuclearAText->SetText("A = ");
	NuclearFrame->AddFrame(NuclearAText, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
	NuclearAText->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
	NuclearAText->SetAlignment(kTextCenterX);
	NuclearAText->Resize(200, 40);
	NuclearAText->SetEnabled(kFALSE);
	NuclearAText->SetFrameDrawn(kFALSE);
	NuclearAText->ChangeBackground(TColor::RGB2Pixel(62, 62, 62));
	NuclearAText->SetTextColor(TColor::RGB2Pixel(131, 131, 131), false);

	NuclearANumber = new TGNumberEntry(NuclearFrame, 0, 0, TGNumberFormat::kNESInteger);
	NuclearFrame->AddFrame(NuclearANumber, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
	NuclearANumber->GetButtonUp()->ChangeOptions(NuclearANumber->GetButtonUp()->GetOptions() ^ kRaisedFrame);
	NuclearANumber->GetButtonDown()->ChangeOptions(NuclearANumber->GetButtonDown()->GetOptions() ^ kRaisedFrame);
	NuclearANumber->GetNumberEntry()->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
	NuclearANumber->Resize(100, 40);
	NuclearANumber->SetNumber(212);
	NuclearANumber->Associate(this);

	NuclearNText = new TGTextEntry(NuclearFrame, new TGTextBuffer(100), 10000);
	NuclearNText->SetText("N = ");
	NuclearFrame->AddFrame(NuclearNText, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
	NuclearNText->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
	NuclearNText->SetAlignment(kTextCenterX);
	NuclearNText->Resize(190, 40);
	NuclearNText->SetEnabled(kFALSE);
	NuclearNText->SetFrameDrawn(kFALSE);
	NuclearNText->ChangeBackground(TColor::RGB2Pixel(62, 62, 62));
	NuclearNText->SetTextColor(TColor::RGB2Pixel(131, 131, 131), false);

	NuclearNNumber = new TGNumberEntry(NuclearFrame, 0, 0, TGNumberFormat::kNESInteger);
	NuclearFrame->AddFrame(NuclearNNumber, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
	NuclearNNumber->GetButtonUp()->ChangeOptions(NuclearNNumber->GetButtonUp()->GetOptions() ^ kRaisedFrame);
	NuclearNNumber->GetButtonDown()->ChangeOptions(NuclearNNumber->GetButtonDown()->GetOptions() ^ kRaisedFrame);
	NuclearNNumber->GetNumberEntry()->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
	NuclearNNumber->Resize(100, 40);
	NuclearNNumber->SetNumber(128);
	NuclearNNumber->Associate(this);
	

	TGHSplitter *hsplitter1 = new TGHSplitter(ThisFrame,800,2);
	ThisFrame->AddFrame(hsplitter1, new TGLayoutHints(kLHintsTop | kLHintsExpandX,0,0,10,10));
	hsplitter1->SetBackgroundColor(TColor::RGB2Pixel(0,0,0));

	CalculateFrame = new TGHorizontalFrame(ThisFrame, 800, 40);
	ThisFrame->AddFrame(CalculateFrame, new TGLayoutHints(kLHintsTop | kLHintsLeft, 0, 0, 0, 0));
	CalculateFrame->SetBackgroundColor(TColor::RGB2Pixel(62, 62, 62));

	ParameterFrame = new TGVerticalFrame(CalculateFrame, 210, 440);
	CalculateFrame->AddFrame(ParameterFrame, new TGLayoutHints(kLHintsTop | kLHintsLeft, 0, 0, 0, 0));
	ParameterFrame->SetBackgroundColor(TColor::RGB2Pixel(62, 62, 62));

	DeltaLFrame = new TGHorizontalFrame(ParameterFrame, 210, 40);
	ParameterFrame->AddFrame(DeltaLFrame, new TGLayoutHints(kLHintsTop | kLHintsLeft, 0, 0, 0, 0));
	DeltaLText = new TGTextEntry(DeltaLFrame, new TGTextBuffer(100), 10000);
	DeltaLText->SetText("L = ");
	DeltaLFrame->AddFrame(DeltaLText, new TGLayoutHints(kLHintsLeft | kLHintsCenterY, 0, 0, 0, 0));
	DeltaLText->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
	DeltaLText->SetAlignment(kTextCenterX);
	DeltaLText->Resize(180, 40);
	DeltaLText->SetEnabled(kFALSE);
	DeltaLText->SetFrameDrawn(kFALSE);
	DeltaLText->ChangeBackground(TColor::RGB2Pixel(62, 62, 62));
	DeltaLText->SetTextColor(TColor::RGB2Pixel(131, 131, 131), false);

	DeltaLNumber = new TGNumberEntry(DeltaLFrame, 0, 0, TGNumberFormat::kNESInteger);
	DeltaLFrame->AddFrame(DeltaLNumber, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
	DeltaLNumber->GetButtonUp()->ChangeOptions(DeltaLNumber->GetButtonUp()->GetOptions() ^ kRaisedFrame);
	DeltaLNumber->GetButtonDown()->ChangeOptions(DeltaLNumber->GetButtonDown()->GetOptions() ^ kRaisedFrame);
	DeltaLNumber->GetNumberEntry()->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
	DeltaLNumber->Resize(150, 40);
	DeltaLNumber->SetNumber(0);
	DeltaLNumber->Associate(this);


	EnergyFrame = new TGHorizontalFrame(ParameterFrame, 210, 40);
	ParameterFrame->AddFrame(EnergyFrame, new TGLayoutHints(kLHintsTop | kLHintsLeft, 0, 0, 0, 0));
	EnergyText = new TGTextEntry(EnergyFrame, new TGTextBuffer(100), 10000);
	EnergyText->SetText("E = (MeV)");
	EnergyFrame->AddFrame(EnergyText, new TGLayoutHints(kLHintsLeft | kLHintsCenterY, 0, 0, 0, 0));
	EnergyText->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
	EnergyText->SetAlignment(kTextCenterX);
	EnergyText->Resize(180, 40);
	EnergyText->SetEnabled(kFALSE);
	EnergyText->SetFrameDrawn(kFALSE);
	EnergyText->ChangeBackground(TColor::RGB2Pixel(62, 62, 62));
	EnergyText->SetTextColor(TColor::RGB2Pixel(131, 131, 131), false);

	EnergyNumber = new TGNumberEntry(EnergyFrame, 0, 0, TGNumberFormat::kNESInteger);
	EnergyFrame->AddFrame(EnergyNumber, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
	EnergyNumber->GetButtonUp()->ChangeOptions(EnergyNumber->GetButtonUp()->GetOptions() ^ kRaisedFrame);
	EnergyNumber->GetButtonDown()->ChangeOptions(EnergyNumber->GetButtonDown()->GetOptions() ^ kRaisedFrame);
	EnergyNumber->GetNumberEntry()->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
	EnergyNumber->Resize(150, 40);
	EnergyNumber->SetNumber(8.78486);
	EnergyNumber->Associate(this);

	HalfLifeFrame = new TGHorizontalFrame(ParameterFrame, 210, 40);
	ParameterFrame->AddFrame(HalfLifeFrame, new TGLayoutHints(kLHintsTop | kLHintsLeft, 0, 0, 0, 0));
	HalfLifeText = new TGTextEntry(HalfLifeFrame, new TGTextBuffer(100), 10000);
	HalfLifeText->SetText("T1/2 = (s)");
	HalfLifeFrame->AddFrame(HalfLifeText, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
	HalfLifeText->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
	HalfLifeText->SetAlignment(kTextCenterX);
	HalfLifeText->Resize(180, 40);
	HalfLifeText->SetEnabled(kFALSE);
	HalfLifeText->SetFrameDrawn(kFALSE);
	HalfLifeText->ChangeBackground(TColor::RGB2Pixel(62, 62, 62));
	HalfLifeText->SetTextColor(TColor::RGB2Pixel(131, 131, 131), false);

	HalfLifeNumber = new TGNumberEntry(HalfLifeFrame, 0, 0, TGNumberFormat::kNESInteger);
	HalfLifeFrame->AddFrame(HalfLifeNumber, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
	HalfLifeNumber->GetButtonUp()->ChangeOptions(HalfLifeNumber->GetButtonUp()->GetOptions() ^ kRaisedFrame);
	HalfLifeNumber->GetButtonDown()->ChangeOptions(HalfLifeNumber->GetButtonDown()->GetOptions() ^ kRaisedFrame);
	HalfLifeNumber->GetNumberEntry()->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
	HalfLifeNumber->Resize(150, 40);
	HalfLifeNumber->SetNumber(0.299E-6);
	HalfLifeNumber->Associate(this);

	HalfLifeErrorPosFrame = new TGHorizontalFrame(ParameterFrame, 210, 40);
	ParameterFrame->AddFrame(HalfLifeErrorPosFrame, new TGLayoutHints(kLHintsTop | kLHintsLeft, 0, 0, 0, 0));
	HalfLifeErrorPosText = new TGTextEntry(HalfLifeErrorPosFrame, new TGTextBuffer(100), 10000);
	HalfLifeErrorPosText->SetText("T1/2(ErrPos) = (s)");
	HalfLifeErrorPosFrame->AddFrame(HalfLifeErrorPosText, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
	HalfLifeErrorPosText->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
	HalfLifeErrorPosText->SetAlignment(kTextCenterX);
	HalfLifeErrorPosText->Resize(180, 40);
	HalfLifeErrorPosText->SetEnabled(kFALSE);
	HalfLifeErrorPosText->SetFrameDrawn(kFALSE);
	HalfLifeErrorPosText->ChangeBackground(TColor::RGB2Pixel(62, 62, 62));
	HalfLifeErrorPosText->SetTextColor(TColor::RGB2Pixel(131, 131, 131), false);

	HalfLifeErrorPosNumber = new TGNumberEntry(HalfLifeErrorPosFrame, 0, 0, TGNumberFormat::kNESInteger);
	HalfLifeErrorPosFrame->AddFrame(HalfLifeErrorPosNumber, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
	HalfLifeErrorPosNumber->GetButtonUp()->ChangeOptions(HalfLifeErrorPosNumber->GetButtonUp()->GetOptions() ^ kRaisedFrame);
	HalfLifeErrorPosNumber->GetButtonDown()->ChangeOptions(HalfLifeErrorPosNumber->GetButtonDown()->GetOptions() ^ kRaisedFrame);
	HalfLifeErrorPosNumber->GetNumberEntry()->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
	HalfLifeErrorPosNumber->Resize(150, 40);
	HalfLifeErrorPosNumber->SetNumber(0.002E-6);
	HalfLifeErrorPosNumber->Associate(this);

	HalfLifeErrorNegFrame = new TGHorizontalFrame(ParameterFrame, 210, 40);
	ParameterFrame->AddFrame(HalfLifeErrorNegFrame, new TGLayoutHints(kLHintsTop | kLHintsLeft, 0, 0, 0, 0));
	HalfLifeErrorNegText = new TGTextEntry(HalfLifeErrorNegFrame, new TGTextBuffer(100), 10000);
	HalfLifeErrorNegText->SetText("T1/2(ErrNeg) = (s)");
	HalfLifeErrorNegFrame->AddFrame(HalfLifeErrorNegText, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
	HalfLifeErrorNegText->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
	HalfLifeErrorNegText->SetAlignment(kTextCenterX);
	HalfLifeErrorNegText->Resize(180, 40);
	HalfLifeErrorNegText->SetEnabled(kFALSE);
	HalfLifeErrorNegText->SetFrameDrawn(kFALSE);
	HalfLifeErrorNegText->ChangeBackground(TColor::RGB2Pixel(62, 62, 62));
	HalfLifeErrorNegText->SetTextColor(TColor::RGB2Pixel(131, 131, 131), false);

	HalfLifeErrorNegNumber = new TGNumberEntry(HalfLifeErrorNegFrame, 0, 0, TGNumberFormat::kNESInteger);
	HalfLifeErrorNegFrame->AddFrame(HalfLifeErrorNegNumber, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
	HalfLifeErrorNegNumber->GetButtonUp()->ChangeOptions(HalfLifeErrorNegNumber->GetButtonUp()->GetOptions() ^ kRaisedFrame);
	HalfLifeErrorNegNumber->GetButtonDown()->ChangeOptions(HalfLifeErrorNegNumber->GetButtonDown()->GetOptions() ^ kRaisedFrame);
	HalfLifeErrorNegNumber->GetNumberEntry()->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
	HalfLifeErrorNegNumber->Resize(150, 40);
	HalfLifeErrorNegNumber->SetNumber(0.002E-6);
	HalfLifeErrorNegNumber->Associate(this);

	RatioFrame = new TGHorizontalFrame(ParameterFrame, 210, 40);
	ParameterFrame->AddFrame(RatioFrame, new TGLayoutHints(kLHintsTop | kLHintsLeft, 0, 0, 0, 0));
	RatioText = new TGTextEntry(RatioFrame, new TGTextBuffer(100), 10000);
	RatioText->SetText("Ratio(%) = ");
	RatioFrame->AddFrame(RatioText, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
	RatioText->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
	RatioText->SetAlignment(kTextCenterX);
	RatioText->Resize(180, 40);
	RatioText->SetEnabled(kFALSE);
	RatioText->SetFrameDrawn(kFALSE);
	RatioText->ChangeBackground(TColor::RGB2Pixel(62, 62, 62));
	RatioText->SetTextColor(TColor::RGB2Pixel(131, 131, 131), false);

	RatioNumber = new TGNumberEntry(RatioFrame, 0, 0, TGNumberFormat::kNESInteger);
	RatioFrame->AddFrame(RatioNumber, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
	RatioNumber->GetButtonUp()->ChangeOptions(RatioNumber->GetButtonUp()->GetOptions() ^ kRaisedFrame);
	RatioNumber->GetButtonDown()->ChangeOptions(RatioNumber->GetButtonDown()->GetOptions() ^ kRaisedFrame);
	RatioNumber->GetNumberEntry()->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
	RatioNumber->Resize(150, 40);
	RatioNumber->SetNumber(100.0);

	ErrorFrame = new TGHorizontalFrame(ParameterFrame, 210, 40);
	ParameterFrame->AddFrame(ErrorFrame, new TGLayoutHints(kLHintsTop | kLHintsLeft, 0, 0, 0, 0));
	ErrorText = new TGTextEntry(ErrorFrame, new TGTextBuffer(100), 10000);
	ErrorText->SetText("Error(r) = ");
	ErrorFrame->AddFrame(ErrorText, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
	ErrorText->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
	ErrorText->SetAlignment(kTextCenterX);
	ErrorText->Resize(180, 40);
	ErrorText->SetEnabled(kFALSE);
	ErrorText->SetFrameDrawn(kFALSE);
	ErrorText->ChangeBackground(TColor::RGB2Pixel(62, 62, 62));
	ErrorText->SetTextColor(TColor::RGB2Pixel(131, 131, 131), false);

	ErrorNumber = new TGNumberEntry(ErrorFrame, 0, 0, TGNumberFormat::kNESInteger);
	ErrorFrame->AddFrame(ErrorNumber, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
	ErrorNumber->GetButtonUp()->ChangeOptions(ErrorNumber->GetButtonUp()->GetOptions() ^ kRaisedFrame);
	ErrorNumber->GetButtonDown()->ChangeOptions(ErrorNumber->GetButtonDown()->GetOptions() ^ kRaisedFrame);
	ErrorNumber->GetNumberEntry()->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
	ErrorNumber->Resize(150, 40);
	ErrorNumber->SetNumber(1.0E-12);
	ErrorNumber->Associate(this);


	CalculateButtonFrame = new TGHorizontalFrame(ParameterFrame, 240, 40);
	ParameterFrame->AddFrame(CalculateButtonFrame, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
	CalculateButtonFrame->SetBackgroundColor(TColor::RGB2Pixel(62, 62, 62));
	CalculateB = new TGTextButton(CalculateButtonFrame, "Calculate", CalculateButton);
    CalculateButtonFrame->AddFrame(CalculateB, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 30, 0, 0, 0));
    CalculateB->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
    CalculateB->Resize(80, 40);
    CalculateB->SetTextColor(TColor::RGB2Pixel(255, 255, 255));
    CalculateB->SetBackgroundColor(TColor::RGB2Pixel(34, 151, 159));
    CalculateB->Associate(this);

	QalphaFrame = new TGHorizontalFrame(ParameterFrame, 210, 40);
	ParameterFrame->AddFrame(QalphaFrame, new TGLayoutHints(kLHintsTop | kLHintsLeft, 0, 0, 0, 0));
	QalphaText = new TGTextEntry(QalphaFrame, new TGTextBuffer(100), 10000);
	QalphaText->SetText("Q = (MeV)");
	QalphaFrame->AddFrame(QalphaText, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
	QalphaText->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
	QalphaText->SetAlignment(kTextCenterX);
	QalphaText->Resize(180, 40);
	QalphaText->SetEnabled(kFALSE);
	QalphaText->SetFrameDrawn(kFALSE);
	QalphaText->ChangeBackground(TColor::RGB2Pixel(62, 62, 62));
	QalphaText->SetTextColor(TColor::RGB2Pixel(131, 131, 131), false);

	QalphaNumber = new TGNumberEntry(QalphaFrame, 0, 0, TGNumberFormat::kNESInteger);
	QalphaFrame->AddFrame(QalphaNumber, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
	QalphaNumber->GetButtonUp()->ChangeOptions(QalphaNumber->GetButtonUp()->GetOptions() ^ kRaisedFrame);
	QalphaNumber->GetButtonDown()->ChangeOptions(QalphaNumber->GetButtonDown()->GetOptions() ^ kRaisedFrame);
	QalphaNumber->GetNumberEntry()->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
	QalphaNumber->Resize(150, 40);
	QalphaNumber->SetNumber(0.0);
	QalphaNumber->Associate(this);

	EtotFrame = new TGHorizontalFrame(ParameterFrame, 210, 40);
	ParameterFrame->AddFrame(EtotFrame, new TGLayoutHints(kLHintsTop | kLHintsLeft, 0, 0, 0, 0));
	EtotText = new TGTextEntry(EtotFrame, new TGTextBuffer(100), 10000);
	EtotText->SetText("E(tot) = (MeV)");
	EtotFrame->AddFrame(EtotText, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
	EtotText->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
	EtotText->SetAlignment(kTextCenterX);
	EtotText->Resize(180, 40);
	EtotText->SetEnabled(kFALSE);
	EtotText->SetFrameDrawn(kFALSE);
	EtotText->ChangeBackground(TColor::RGB2Pixel(62, 62, 62));
	EtotText->SetTextColor(TColor::RGB2Pixel(131, 131, 131), false);

	EtotNumber = new TGNumberEntry(EtotFrame, 0, 0, TGNumberFormat::kNESInteger);
	EtotFrame->AddFrame(EtotNumber, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
	EtotNumber->GetButtonUp()->ChangeOptions(EtotNumber->GetButtonUp()->GetOptions() ^ kRaisedFrame);
	EtotNumber->GetButtonDown()->ChangeOptions(EtotNumber->GetButtonDown()->GetOptions() ^ kRaisedFrame);
	EtotNumber->GetNumberEntry()->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
	EtotNumber->Resize(150, 40);
	EtotNumber->SetNumber(0.0);
	EtotNumber->Associate(this);

	IntegrationFrame = new TGHorizontalFrame(ParameterFrame, 210, 40);
	ParameterFrame->AddFrame(IntegrationFrame, new TGLayoutHints(kLHintsTop | kLHintsLeft, 0, 0, 0, 0));
	IntegrationText = new TGTextEntry(IntegrationFrame, new TGTextBuffer(100), 10000);
	IntegrationText->SetText("Integration = ");
	IntegrationFrame->AddFrame(IntegrationText, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
	IntegrationText->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
	IntegrationText->SetAlignment(kTextCenterX);
	IntegrationText->Resize(180, 40);
	IntegrationText->SetEnabled(kFALSE);
	IntegrationText->SetFrameDrawn(kFALSE);
	IntegrationText->ChangeBackground(TColor::RGB2Pixel(62, 62, 62));
	IntegrationText->SetTextColor(TColor::RGB2Pixel(131, 131, 131), false);

	IntegrationNumber = new TGNumberEntry(IntegrationFrame, 0, 0, TGNumberFormat::kNESInteger);
	IntegrationFrame->AddFrame(IntegrationNumber, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
	IntegrationNumber->GetButtonUp()->ChangeOptions(IntegrationNumber->GetButtonUp()->GetOptions() ^ kRaisedFrame);
	IntegrationNumber->GetButtonDown()->ChangeOptions(IntegrationNumber->GetButtonDown()->GetOptions() ^ kRaisedFrame);
	IntegrationNumber->GetNumberEntry()->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
	IntegrationNumber->Resize(150, 40);
	IntegrationNumber->SetNumber(0);
	IntegrationNumber->Associate(this);

	PenetrationFrame = new TGHorizontalFrame(ParameterFrame, 210, 40);
	ParameterFrame->AddFrame(PenetrationFrame, new TGLayoutHints(kLHintsTop | kLHintsLeft, 0, 0, 0, 0));
	PenetrationText = new TGTextEntry(PenetrationFrame, new TGTextBuffer(100), 10000);
	PenetrationText->SetText("P factor = ");
	PenetrationFrame->AddFrame(PenetrationText, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
	PenetrationText->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
	PenetrationText->SetAlignment(kTextCenterX);
	PenetrationText->Resize(180, 40);
	PenetrationText->SetEnabled(kFALSE);
	PenetrationText->SetFrameDrawn(kFALSE);
	PenetrationText->ChangeBackground(TColor::RGB2Pixel(62, 62, 62));
	PenetrationText->SetTextColor(TColor::RGB2Pixel(131, 131, 131), false);

	PenetrationNumber = new TGNumberEntry(PenetrationFrame, 0, 0, TGNumberFormat::kNESInteger);
	PenetrationFrame->AddFrame(PenetrationNumber, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
	PenetrationNumber->GetButtonUp()->ChangeOptions(PenetrationNumber->GetButtonUp()->GetOptions() ^ kRaisedFrame);
	PenetrationNumber->GetButtonDown()->ChangeOptions(PenetrationNumber->GetButtonDown()->GetOptions() ^ kRaisedFrame);
	PenetrationNumber->GetNumberEntry()->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
	PenetrationNumber->Resize(150, 40);
	PenetrationNumber->SetNumber(0);
	PenetrationNumber->Associate(this);


	RDWFrame = new TGHorizontalFrame(ParameterFrame, 210, 40);
	ParameterFrame->AddFrame(RDWFrame, new TGLayoutHints(kLHintsTop | kLHintsLeft, 0, 0, 0, 0));
	RDWText = new TGTextEntry(RDWFrame, new TGTextBuffer(100), 10000);
	RDWText->SetText("RDW(even-even) ");
	RDWFrame->AddFrame(RDWText, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
	RDWText->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
	RDWText->SetAlignment(kTextCenterX);
	RDWText->Resize(180, 40);
	RDWText->SetEnabled(kFALSE);
	RDWText->SetFrameDrawn(kFALSE);
	RDWText->ChangeBackground(TColor::RGB2Pixel(62, 62, 62));
	RDWText->SetTextColor(TColor::RGB2Pixel(131, 131, 131), false);

	RDWNumber = new TGNumberEntry(RDWFrame, 0, 0, TGNumberFormat::kNESInteger);
	RDWFrame->AddFrame(RDWNumber, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
	RDWNumber->GetButtonUp()->ChangeOptions(RDWNumber->GetButtonUp()->GetOptions() ^ kRaisedFrame);
	RDWNumber->GetButtonDown()->ChangeOptions(RDWNumber->GetButtonDown()->GetOptions() ^ kRaisedFrame);
	RDWNumber->GetNumberEntry()->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
	RDWNumber->Resize(150, 40);
	RDWNumber->SetNumber(70.34);
	RDWNumber->Associate(this);

	CanvasFrame = new TGVerticalFrame(CalculateFrame, 890, 600);
	CalculateFrame->AddFrame(CanvasFrame, new TGLayoutHints(kLHintsTop | kLHintsRight, 0, 0, 0, 0));
	CanvasFrame->SetBackgroundColor(TColor::RGB2Pixel(62, 62, 62));
	FrameCanvas = new TRootEmbeddedCanvas("AlphaDecayReducedWidth", CanvasFrame, 890, 600);
	CanvasFrame->AddFrame(FrameCanvas, new TGLayoutHints(kLHintsExpandX | kLHintsExpandY, 0, 0, 0, 0));
	Int_t wid = FrameCanvas->GetCanvasWindowId();
	TCanvas *can  = new TCanvas("Canvas", 890, 600, wid);
	can->ToggleEventStatus();
	can->Connect("ProcessedEvent(Int_t,Int_t,Int_t,TObject*)", "gui", this, "EventInfo(Int_t,Int_t,Int_t,TObject*)");
	FrameCanvas->AdoptCanvas(can);


	MapSubwindows();
	Resize();
	CenterOnParent();
	SetWindowName(name);
	MapWindow();
	Calculate();
}

alphadecayreducedwidth::~alphadecayreducedwidth(){}

Bool_t alphadecayreducedwidth::ProcessMessage(Long_t msg,Long_t parm1, Long_t parm2)
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
							Calculate();
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

//---------Alpha-nuclear potential
Double_t Vn(Double_t *x, Double_t *Massnum)		// MeV
{
	Double_t Vn=-1100*TMath::Exp(-((x[0]-1.17*TMath::Power(Massnum[0],1./3.))/0.574));
//	if(Vn<-10.) Vn=-10;
	return Vn;
}

//--------- Coulomb potential
Double_t Vc(Double_t *x, Double_t *Chargenum)	// MeV
{
		Double_t Invfine=137.03599911;   // 1/apha
		Double_t Hbarc=197.326968;			// MeV*fm
		Double_t eSqua=Hbarc/Invfine;
	Double_t Vc=2.*Chargenum[0]*eSqua/x[0];
	return Vc;
}

//--------- Centrifugal potential
Double_t Vcent(Double_t *x, Double_t *par)		// MeV
{
	Double_t Hbarc=197.326968;			// MeV*fm
	Double_t U0=931.494043;				// MeV/c2
	Double_t Rmass=4.*par[0]/(4.+par[0])*U0;
	Double_t Vcent=par[1]*(par[1]+1.)*Hbarc*Hbarc/(2.*Rmass*x[0]*x[0]);
	return Vcent;
}

//--------- Total potential
Double_t Vtot(Double_t *x, Double_t *par)		// MeV
{
	Double_t Vtot1=Vn(x,&par[0])+Vc(x,&par[1])+Vcent(x,&par[2]);
	return Vtot1;
}

//--------- Function for integration
Double_t Func(double_t *x, double_t *par)
{
	Double_t Funct=TMath::Sqrt(Vtot(x,par)-par[4]);
	return Funct;
}
void alphadecayreducedwidth::Calculate()
{
	Delta2 = 0.0;
	Delta2err = 0.0;
	const Double_t Invfine=137.03599911;   // 1/apha
	const Double_t Hbarc=197.326968;			// MeV*fm
	const Double_t U0=931.494043;				// MeV/c2
	Double_t Hplk=6.6260693E-34/1E6/1.60217653E-19;				// MeV*s
	Double_t eSqua=Hbarc/Invfine;
	Double_t A,Z,Escr,Qalpha,Etot;
	Double_t Am = Double_t(NuclearANumber->GetNumber()); 
	Double_t Zm = Double_t(NuclearZNumber->GetNumber());
	Double_t Nm = Double_t(NuclearNNumber->GetNumber());
	NuclearNNumber->GetNumberEntry()->SetTextColor(TColor::RGB2Pixel(0, 0, 0));
	if(abs(Am - Zm -Nm) > 0.1)
	{
		NuclearNNumber->SetNumber(Int_t(Am-Zm));
		NuclearNNumber->GetNumberEntry()->SetTextColor(TColor::RGB2Pixel(255, 0, 0));
	}
	Double_t L= Double_t(DeltaLNumber->GetNumber());
	A=Am-4.; 
	Z=Zm-2.;
	Double_t Ealpha = Double_t(EnergyNumber->GetNumber());					// MeV
	Double_t T_half_life = Double_t(HalfLifeNumber->GetNumber());			// s
	Double_t T_pos_err = Double_t(HalfLifeErrorPosNumber->GetNumber());				// s
	Double_t T_neg_err = Double_t(HalfLifeErrorNegNumber->GetNumber());				// s
	Double_t Intensity = Double_t(RatioNumber->GetNumber())/100.0;

//---------------------------------------------------	
	Double_t Rmass=4.*A/(4.+A)*U0;			// MeV/c2
	Double_t Rout, Rin;						// fm
	Double_t array[4]={A,Z,A,L};
	Double_t rx, r0, r1, r;
	Double_t error=1E-12;
	Int_t i=0;
	
//--------- Potential plot
/*
	TCanvas *c1 = new TCanvas("c1","c1",0,0,600,500);
	c1->SetLogy(1);
	c1->Divide(2,2);
	c1->cd(1);
		TF1 *V=new TF1("Vn+Vc+Vcent",Vtot,7,50,4);
		V->SetParameters(A,Z,A,L);
		V->Draw();
	c1->cd(2);
		TF1 *VnTmp=new TF1("Vn",Vn,7,12,1);
		VnTmp->SetParameter(0,A);
		VnTmp->Draw();
		
	c1->cd(3);
		TF1 *VcTmp=new TF1("Vc",Vc,7,12,1);
		VcTmp->SetParameter(0,Z);
		VcTmp->Draw();
		
	c1->cd(4);
		TF1 *VcentTmp=new TF1("Vcent",Vcent,7,12,2);
		VcentTmp->SetParameters(A,L);
		VcentTmp->Draw();
		*/
//
//--------- Total decay energy
	Escr=(65.3*TMath::Power(Zm,7./5.)-80.*TMath::Power(Zm,2./5.))/1E6;	// MeV -> electron-screening correction
	Qalpha=Ealpha+4./A*Ealpha;			// MeV
	Etot=Qalpha+Escr;					// MeV	///////////////////////
//	cout<<"Qalpha = "<<Qalpha<<" MeV"<<endl;
//	cout<<"Etot = "<<Etot<<" MeV"<<endl;

//--------- Outer turning point
	Rout=Z*eSqua/Etot+TMath::Sqrt(Z*Z*eSqua*eSqua+Etot*Hbarc*Hbarc*L*(L+1)/2./Rmass)/Etot;
//	cout<<"Rout = "<<Rout<<" fm"<<endl;
	
//--------- Inner turning point
	for(rx=Rout-0.2; rx>0; rx=rx-0.2)
	{
		r=rx;
		if(Vtot(&r,array)<Etot) break;
	}
	r0=r; 
	r1=r+0.2;
	while(1)
	{
		r=r1-(Vtot(&r1,array)-Etot)*(r1-r0)/(Vtot(&r1,array)-Vtot(&r0,array));
		if( TMath::Abs(r-r1)/r<error ) break;
		r0=r1;  r1=r;  i++;
	}
	Rin=r;
//	cout<<"Rin = "<<Rin<<" fm"<<" (iterative number "<<i<<")"<<endl;
	
//--------- Integration
	TF1 *Func1 = new TF1("Func",Func, Rin, Rout,5);
	Func1->SetParameters(A,Z,A,L,Etot);
	Double_t Integration=Func1->Integral(Rin,Rout);
//	cout<<"Integration = "<<Integration<<endl;
	
//--------- Penetration factor
	Double_t Penetration=TMath::Exp(-2.*TMath::Sqrt(2.*Rmass)*Integration/Hbarc);
//	cout<<"Penetration factor: P = "<<Penetration<<endl;
	
//--------- Reduced alpha decay width
	Double_t DeltSqua=Hplk*(TMath::Log(2)/T_half_life*Intensity)/Penetration*1000.;
	Double_t DeltSqua_pos_err=Hplk*(TMath::Log(2)/T_half_life/T_half_life*Intensity)/Penetration*1000.*T_pos_err;
	Double_t DeltSqua_neg_err=Hplk*(TMath::Log(2)/T_half_life/T_half_life*Intensity)/Penetration*1000.*T_neg_err;
	Delta2 = DeltSqua;
	if(DeltSqua_pos_err > DeltSqua_neg_err)
		Delta2err = DeltSqua_pos_err;
	else
		Delta2err = DeltSqua_neg_err;

//	cout<<"Reduced alpha decay width: Delta^2 = "<<DeltSqua<<" (+"<<DeltSqua_pos_err<<" / -"<<DeltSqua_neg_err<<") keV"<<endl;
	QalphaNumber->SetNumber(Qalpha);
	EtotNumber->SetNumber(Etot);
	IntegrationNumber->SetNumber(Integration);
	PenetrationNumber->SetNumber(Penetration);
	TCanvas *DrawCanvastmp = FrameCanvas->GetCanvas();
	TF1 *V=new TF1("Vn+Vc+Vcent",Vtot,7,50,4);
	V->SetParameters(A,Z,A,L);
	V->SetTitle(";R (fm); Potential (MeV)");
	V->GetXaxis()->CenterTitle("1");
	V->GetYaxis()->CenterTitle("1");
	DrawCanvastmp->cd();
	V->SetLineWidth(3);
	V->SetLineColor(kRed);
	V->SetMarkerColor(kRed);
	V->Draw("PL");
	TArrow *arrow = new TArrow(Rin, V->Eval(Rin), Rout, V->Eval(Rout), 0.01, "<|>");
	arrow->SetFillColor(kBlue);
	arrow->SetLineColor(kBlue);
	arrow->SetFillStyle(1001);
	arrow->SetLineWidth(2);
	arrow->Draw();
	Double_t Delta2_ref = Double_t(RDWNumber->GetNumber()); 
	Double_t HF_tmp = Delta2_ref / Delta2;
//	std::cout << "HF    " << HF_tmp << std::endl;
	TLatex *tex = new TLatex(30, V->GetXaxis()->GetXmax()/2.0, Form("#splitline{#delta^{2} = %0.2f #splitline{+%0.2f}{-%0.2f} keV}{HF = %0.2f}", DeltSqua, DeltSqua_pos_err, DeltSqua_neg_err, HF_tmp));
	tex->SetTextFont(12);
	tex->SetTextSize(0.05);
	tex->Draw();
	DrawCanvastmp->SetLogy(1);
	DrawCanvastmp->Update();

}

