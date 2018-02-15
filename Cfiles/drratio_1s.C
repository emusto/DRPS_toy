void drratio_1s()
{
//=========Macro generated from canvas: c1_n55/c1_n55
//=========  (Mon Mar 20 11:19:04 2017) by ROOT version6.04/00
   TCanvas *c1_n55 = new TCanvas("c1_n55", "c1_n55",0,0,700,500);
   gStyle->SetOptStat(0);
   c1_n55->SetHighLightColor(2);
   c1_n55->Range(0,0,1,1);
   c1_n55->SetFillColor(0);
   c1_n55->SetBorderMode(0);
   c1_n55->SetBorderSize(2);
   c1_n55->SetFrameBorderMode(0);
   
   TH2D *drratio1_1s_vs_z__15 = new TH2D("drratio1_1s_vs_z__15","Ouside/Internal Dose Rate ratio, 1s avg",201,0,201,100,0,2e-05);
   drratio1_1s_vs_z__15->SetBinContent(5073,600);
   drratio1_1s_vs_z__15->SetBinContent(10048,600);
   drratio1_1s_vs_z__15->SetBinContent(11978,600);
   drratio1_1s_vs_z__15->SetEntries(1800);
   drratio1_1s_vs_z__15->GetXaxis()->SetTitle("z source (cm)");
   drratio1_1s_vs_z__15->GetXaxis()->SetLabelFont(42);
   drratio1_1s_vs_z__15->GetXaxis()->SetLabelSize(0.035);
   drratio1_1s_vs_z__15->GetXaxis()->SetTitleSize(0.035);
   drratio1_1s_vs_z__15->GetXaxis()->SetTitleFont(42);
   drratio1_1s_vs_z__15->GetYaxis()->SetTitle("Ratio");
   drratio1_1s_vs_z__15->GetYaxis()->SetLabelFont(42);
   drratio1_1s_vs_z__15->GetYaxis()->SetLabelSize(0.035);
   drratio1_1s_vs_z__15->GetYaxis()->SetTitleSize(0.035);
   drratio1_1s_vs_z__15->GetYaxis()->SetTitleFont(42);
   drratio1_1s_vs_z__15->GetZaxis()->SetLabelFont(42);
   drratio1_1s_vs_z__15->GetZaxis()->SetLabelSize(0.035);
   drratio1_1s_vs_z__15->GetZaxis()->SetTitleSize(0.035);
   drratio1_1s_vs_z__15->GetZaxis()->SetTitleFont(42);
   drratio1_1s_vs_z__15->Draw("");
   
   TH2D *drratio2_1s_vs_z__16 = new TH2D("drratio2_1s_vs_z__16","Outside/Internal Dose Rate ratio, 1s avg",201,0,201,100,0,2e-05);
   drratio2_1s_vs_z__16->SetBinContent(4873,600);
   drratio2_1s_vs_z__16->SetBinContent(10048,600);
   drratio2_1s_vs_z__16->SetBinContent(12178,600);
   drratio2_1s_vs_z__16->SetEntries(1800);
   drratio2_1s_vs_z__16->SetLineColor(2);
   drratio2_1s_vs_z__16->SetMarkerColor(2);
   drratio2_1s_vs_z__16->GetXaxis()->SetLabelFont(42);
   drratio2_1s_vs_z__16->GetXaxis()->SetLabelSize(0.035);
   drratio2_1s_vs_z__16->GetXaxis()->SetTitleSize(0.035);
   drratio2_1s_vs_z__16->GetXaxis()->SetTitleFont(42);
   drratio2_1s_vs_z__16->GetYaxis()->SetLabelFont(42);
   drratio2_1s_vs_z__16->GetYaxis()->SetLabelSize(0.035);
   drratio2_1s_vs_z__16->GetYaxis()->SetTitleSize(0.035);
   drratio2_1s_vs_z__16->GetYaxis()->SetTitleFont(42);
   drratio2_1s_vs_z__16->GetZaxis()->SetLabelFont(42);
   drratio2_1s_vs_z__16->GetZaxis()->SetLabelSize(0.035);
   drratio2_1s_vs_z__16->GetZaxis()->SetTitleSize(0.035);
   drratio2_1s_vs_z__16->GetZaxis()->SetTitleFont(42);
   drratio2_1s_vs_z__16->Draw("same");
   
   TLegend *leg = new TLegend(-2.353437e-185,-2.353437e-185,-2.353437e-185,-2.353437e-185,NULL,"brNDC");
   leg->SetBorderSize(1);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("drratio1_1s_vs_z","Detector 1 (z=0 cm)","lp");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry=leg->AddEntry("drratio2_1s_vs_z","Detector 2 (z=200 cm)","lp");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   leg->Draw();
   c1_n55->Modified();
   c1_n55->cd();
   c1_n55->SetSelected(c1_n55);
}
