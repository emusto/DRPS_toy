void drratio_1m()
{
//=========Macro generated from canvas: c1_n58/c1_n58
//=========  (Mon Mar 20 11:19:04 2017) by ROOT version6.04/00
   TCanvas *c1_n58 = new TCanvas("c1_n58", "c1_n58",0,0,700,500);
   gStyle->SetOptStat(0);
   c1_n58->SetHighLightColor(2);
   c1_n58->Range(0,0,1,1);
   c1_n58->SetFillColor(0);
   c1_n58->SetBorderMode(0);
   c1_n58->SetBorderSize(2);
   c1_n58->SetFrameBorderMode(0);
   
   TH2D *drratio1_1m_vs_z__22 = new TH2D("drratio1_1m_vs_z__22","Outside/Internal Dose Rate ratio, 1m avg",201,0,201,100,0,2e-05);
   drratio1_1m_vs_z__22->SetBinContent(5073,10);
   drratio1_1m_vs_z__22->SetBinContent(10048,10);
   drratio1_1m_vs_z__22->SetBinContent(11978,10);
   drratio1_1m_vs_z__22->SetEntries(30);
   drratio1_1m_vs_z__22->GetXaxis()->SetTitle("z source (cm)");
   drratio1_1m_vs_z__22->GetXaxis()->SetLabelFont(42);
   drratio1_1m_vs_z__22->GetXaxis()->SetLabelSize(0.035);
   drratio1_1m_vs_z__22->GetXaxis()->SetTitleSize(0.035);
   drratio1_1m_vs_z__22->GetXaxis()->SetTitleFont(42);
   drratio1_1m_vs_z__22->GetYaxis()->SetTitle("Ratio");
   drratio1_1m_vs_z__22->GetYaxis()->SetLabelFont(42);
   drratio1_1m_vs_z__22->GetYaxis()->SetLabelSize(0.035);
   drratio1_1m_vs_z__22->GetYaxis()->SetTitleSize(0.035);
   drratio1_1m_vs_z__22->GetYaxis()->SetTitleFont(42);
   drratio1_1m_vs_z__22->GetZaxis()->SetLabelFont(42);
   drratio1_1m_vs_z__22->GetZaxis()->SetLabelSize(0.035);
   drratio1_1m_vs_z__22->GetZaxis()->SetTitleSize(0.035);
   drratio1_1m_vs_z__22->GetZaxis()->SetTitleFont(42);
   drratio1_1m_vs_z__22->Draw("");
   
   TH2D *drratio2_1m_vs_z__23 = new TH2D("drratio2_1m_vs_z__23","Outside/Internal Dose Rate ratio, 1m avg",201,0,201,100,0,2e-05);
   drratio2_1m_vs_z__23->SetBinContent(4873,10);
   drratio2_1m_vs_z__23->SetBinContent(10048,10);
   drratio2_1m_vs_z__23->SetBinContent(12178,10);
   drratio2_1m_vs_z__23->SetEntries(30);
   drratio2_1m_vs_z__23->SetLineColor(2);
   drratio2_1m_vs_z__23->SetMarkerColor(2);
   drratio2_1m_vs_z__23->GetXaxis()->SetLabelFont(42);
   drratio2_1m_vs_z__23->GetXaxis()->SetLabelSize(0.035);
   drratio2_1m_vs_z__23->GetXaxis()->SetTitleSize(0.035);
   drratio2_1m_vs_z__23->GetXaxis()->SetTitleFont(42);
   drratio2_1m_vs_z__23->GetYaxis()->SetLabelFont(42);
   drratio2_1m_vs_z__23->GetYaxis()->SetLabelSize(0.035);
   drratio2_1m_vs_z__23->GetYaxis()->SetTitleSize(0.035);
   drratio2_1m_vs_z__23->GetYaxis()->SetTitleFont(42);
   drratio2_1m_vs_z__23->GetZaxis()->SetLabelFont(42);
   drratio2_1m_vs_z__23->GetZaxis()->SetLabelSize(0.035);
   drratio2_1m_vs_z__23->GetZaxis()->SetTitleSize(0.035);
   drratio2_1m_vs_z__23->GetZaxis()->SetTitleFont(42);
   drratio2_1m_vs_z__23->Draw("same");
   
   TLegend *leg = new TLegend(-2.353437e-185,-2.353437e-185,-2.353437e-185,-2.353437e-185,NULL,"brNDC");
   leg->SetBorderSize(1);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("drratio1_1m_vs_z","Detector 1 (z=0 cm)","lp");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry=leg->AddEntry("drratio2_1m_vs_z","Detector 2 (z=200 cm)","lp");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   leg->Draw();
   c1_n58->Modified();
   c1_n58->cd();
   c1_n58->SetSelected(c1_n58);
}
