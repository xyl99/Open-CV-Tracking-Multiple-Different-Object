#pragma once
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include "jackylib.h"
#include <stdio.h>
#include <iostream>
#include <conio.h> 
namespace OpenCV_Ball_Detector {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace std;
	using namespace cv;
	using namespace jacky_lib;

	bool calibrationMode;//nampilin window kalibrasi
	bool mouseIsDragging;//nampilin klik&drag user
	bool mouseMove;
	bool rectangleSelected;
	cv::Point initialClickPoint, currentMousePoint; //track posisi click&mousenya
	cv::Rect rectangleROI; //range yg sudah dipilih
	vector<int> H_ROI, S_ROI, V_ROI;// buat nyimpen hsv min max
	
	const int FRAME_WIDTH = 640;
	const int FRAME_HEIGHT = 480;
	const int MIN_OBJECT_AREA = 20 * 20;
	const int MAX_OBJECT_AREA = FRAME_HEIGHT*FRAME_WIDTH / 3;
	Mat cameraframe;
	mat2picture mat2bmp;
	Mat inrImg;
	Mat hvsImg;
	Mat srcImg;
	Mat grayImg;
	Mat canyImg;
	Mat blurImg;
	Mat hvs_filer;
	int Hmax, Hmin, Vmax, Vmin, Smax, Smin;
	int Max_obj = 50;
	int xm, ym;
	num2str n2str;

	/// <summary>
	/// Summary for MainForm
	/// </summary>
	void clickAndDrag_Rectangle(int event, int x, int y, int flags, void* param) {

		//klo calibrationnya di teken, pake mouse aja buat ngatur hsv nya
		if (calibrationMode == true) {
			//nanti jadi parameter buat di videonya trus jadi mat pointer
			Mat* videoFeed = (Mat*)param;

			if (event == CV_EVENT_LBUTTONDOWN && mouseIsDragging == false)
			{
				//nge track titik awal
				initialClickPoint = cv::Point(x, y);
				//drag mouse nya
				mouseIsDragging = true;
			}
			/* mousenya di drag */
			if (event == CV_EVENT_MOUSEMOVE && mouseIsDragging == true)
			{
				currentMousePoint = cv::Point(x, y);
				mouseMove = true;
			}
			/* dah dapet range nya */
			if (event == CV_EVENT_LBUTTONUP && mouseIsDragging == true)
			{
				//objek terpilih di range persegi
				rectangleROI = Rect(initialClickPoint, currentMousePoint);

				//bolean pilih objek di reset
				mouseIsDragging = false;
				mouseMove = false;
				rectangleSelected = true;
			}

			if (event == CV_EVENT_RBUTTONDOWN) {
				//klik kanan mmouse = reset hsv
				Hmin = 0;
				Smin = 0;
				Vmin = 0;
				Hmax = 255;
				Smax = 255;
				Vmax = 255;

			}
		}
		
	}

	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}
#pragma region Install Window Form Component
//bikin form
	protected:
		/// <summary>
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  btnBrowser;
	private: System::Windows::Forms::PictureBox^  ptbVideo;
	private: System::Windows::Forms::Button^  btnProcess;
	private: System::Windows::Forms::TrackBar^  trbHmin;
	private: System::Windows::Forms::TrackBar^  trbHmax;
	private: System::Windows::Forms::TrackBar^  trbVmin;
	private: System::Windows::Forms::TrackBar^  trbVmax;
	private: System::Windows::Forms::TrackBar^  trbSmax;
	private: System::Windows::Forms::TrackBar^  trbSmin;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::TextBox^  txbHmax;
	private: System::Windows::Forms::TextBox^  txbHmin;
	private: System::Windows::Forms::TextBox^  txbVmax;
	private: System::Windows::Forms::TextBox^  txbVmin;
	private: System::Windows::Forms::TextBox^  txbSmax;
	private: System::Windows::Forms::TextBox^  txbSmin;

	protected:

	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->btnBrowser = (gcnew System::Windows::Forms::Button());
			this->ptbVideo = (gcnew System::Windows::Forms::PictureBox());
			this->btnProcess = (gcnew System::Windows::Forms::Button());
			this->trbHmin = (gcnew System::Windows::Forms::TrackBar());
			this->trbHmax = (gcnew System::Windows::Forms::TrackBar());
			this->trbVmin = (gcnew System::Windows::Forms::TrackBar());
			this->trbVmax = (gcnew System::Windows::Forms::TrackBar());
			this->trbSmax = (gcnew System::Windows::Forms::TrackBar());
			this->trbSmin = (gcnew System::Windows::Forms::TrackBar());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->txbHmax = (gcnew System::Windows::Forms::TextBox());
			this->txbHmin = (gcnew System::Windows::Forms::TextBox());
			this->txbVmax = (gcnew System::Windows::Forms::TextBox());
			this->txbVmin = (gcnew System::Windows::Forms::TextBox());
			this->txbSmax = (gcnew System::Windows::Forms::TextBox());
			this->txbSmin = (gcnew System::Windows::Forms::TextBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ptbVideo))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trbHmin))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trbHmax))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trbVmin))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trbVmax))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trbSmax))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trbSmin))->BeginInit();
			this->SuspendLayout();
			// 
			// btnBrowser
			// 
			this->btnBrowser->Location = System::Drawing::Point(12, 12);
			this->btnBrowser->Name = L"btnBrowser";
			this->btnBrowser->Size = System::Drawing::Size(75, 23);
			this->btnBrowser->TabIndex = 0;
			this->btnBrowser->Text = L"Video";
			this->btnBrowser->UseVisualStyleBackColor = true;
			this->btnBrowser->Click += gcnew System::EventHandler(this, &MainForm::btnBrowser_Click);
			// 
			// ptbVideo
			// 
			this->ptbVideo->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->ptbVideo->Location = System::Drawing::Point(289, 50);
			this->ptbVideo->Name = L"ptbVideo";
			this->ptbVideo->Size = System::Drawing::Size(437, 284);
			this->ptbVideo->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->ptbVideo->TabIndex = 1;
			this->ptbVideo->TabStop = false;
			// 
			// btnProcess
			// 
			this->btnProcess->Location = System::Drawing::Point(93, 12);
			this->btnProcess->Name = L"btnProcess";
			this->btnProcess->Size = System::Drawing::Size(85, 23);
			this->btnProcess->TabIndex = 0;
			this->btnProcess->Text = L"Kalibrasi";
			this->btnProcess->UseVisualStyleBackColor = true;
			this->btnProcess->Click += gcnew System::EventHandler(this, &MainForm::btnProcess_Click);
			// 
			// trbHmin
			// 
			this->trbHmin->Location = System::Drawing::Point(49, 51);
			this->trbHmin->Maximum = 500;
			this->trbHmin->Name = L"trbHmin";
			this->trbHmin->Size = System::Drawing::Size(186, 45);
			this->trbHmin->TabIndex = 2;
			this->trbHmin->Value = 500;
			// 
			// trbHmax
			// 
			this->trbHmax->Location = System::Drawing::Point(49, 102);
			this->trbHmax->Maximum = 500;
			this->trbHmax->Name = L"trbHmax";
			this->trbHmax->Size = System::Drawing::Size(186, 45);
			this->trbHmax->TabIndex = 2;
			// 
			// trbVmin
			// 
			this->trbVmin->Location = System::Drawing::Point(49, 153);
			this->trbVmin->Maximum = 500;
			this->trbVmin->Name = L"trbVmin";
			this->trbVmin->Size = System::Drawing::Size(186, 45);
			this->trbVmin->TabIndex = 2;
			this->trbVmin->Value = 500;
			// 
			// trbVmax
			// 
			this->trbVmax->Location = System::Drawing::Point(49, 204);
			this->trbVmax->Maximum = 500;
			this->trbVmax->Name = L"trbVmax";
			this->trbVmax->Size = System::Drawing::Size(186, 45);
			this->trbVmax->TabIndex = 2;
			// 
			// trbSmax
			// 
			this->trbSmax->Location = System::Drawing::Point(49, 306);
			this->trbSmax->Maximum = 500;
			this->trbSmax->Name = L"trbSmax";
			this->trbSmax->Size = System::Drawing::Size(186, 45);
			this->trbSmax->TabIndex = 2;
			// 
			// trbSmin
			// 
			this->trbSmin->Location = System::Drawing::Point(49, 255);
			this->trbSmin->Maximum = 500;
			this->trbSmin->Name = L"trbSmin";
			this->trbSmin->Size = System::Drawing::Size(186, 45);
			this->trbSmin->TabIndex = 2;
			this->trbSmin->Value = 500;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(8, 51);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(34, 13);
			this->label1->TabIndex = 3;
			this->label1->Text = L"Hmax";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(8, 153);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(33, 13);
			this->label2->TabIndex = 3;
			this->label2->Text = L"Vmax";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(8, 255);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(33, 13);
			this->label3->TabIndex = 3;
			this->label3->Text = L"Smax";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(7, 102);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(31, 13);
			this->label4->TabIndex = 3;
			this->label4->Text = L"Hmin";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(8, 204);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(30, 13);
			this->label5->TabIndex = 3;
			this->label5->Text = L"Vmin";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(7, 306);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(30, 13);
			this->label6->TabIndex = 3;
			this->label6->Text = L"Smin";
			// 
			// txbHmax
			// 
			this->txbHmax->Location = System::Drawing::Point(241, 51);
			this->txbHmax->Name = L"txbHmax";
			this->txbHmax->Size = System::Drawing::Size(42, 20);
			this->txbHmax->TabIndex = 4;
			// 
			// txbHmin
			// 
			this->txbHmin->Location = System::Drawing::Point(241, 102);
			this->txbHmin->Name = L"txbHmin";
			this->txbHmin->Size = System::Drawing::Size(42, 20);
			this->txbHmin->TabIndex = 4;
			// 
			// txbVmax
			// 
			this->txbVmax->Location = System::Drawing::Point(241, 153);
			this->txbVmax->Name = L"txbVmax";
			this->txbVmax->Size = System::Drawing::Size(42, 20);
			this->txbVmax->TabIndex = 4;
			// 
			// txbVmin
			// 
			this->txbVmin->Location = System::Drawing::Point(241, 204);
			this->txbVmin->Name = L"txbVmin";
			this->txbVmin->Size = System::Drawing::Size(42, 20);
			this->txbVmin->TabIndex = 4;
			// 
			// txbSmax
			// 
			this->txbSmax->Location = System::Drawing::Point(241, 255);
			this->txbSmax->Name = L"txbSmax";
			this->txbSmax->Size = System::Drawing::Size(42, 20);
			this->txbSmax->TabIndex = 4;
			// 
			// txbSmin
			// 
			this->txbSmin->Location = System::Drawing::Point(241, 306);
			this->txbSmin->Name = L"txbSmin";
			this->txbSmin->Size = System::Drawing::Size(42, 20);
			this->txbSmin->TabIndex = 4;
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(738, 346);
			this->Controls->Add(this->txbSmin);
			this->Controls->Add(this->txbSmax);
			this->Controls->Add(this->txbVmin);
			this->Controls->Add(this->txbVmax);
			this->Controls->Add(this->txbHmin);
			this->Controls->Add(this->txbHmax);
			this->Controls->Add(this->trbSmax);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->trbSmin);
			this->Controls->Add(this->trbVmax);
			this->Controls->Add(this->trbVmin);
			this->Controls->Add(this->trbHmax);
			this->Controls->Add(this->trbHmin);
			//this->Controls->Add(this->ptbVideo);
			this->Controls->Add(this->btnProcess);
			this->Controls->Add(this->btnBrowser);
			this->Name = L"MainForm";
			this->Text = L"iyain";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ptbVideo))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trbHmin))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trbHmax))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trbVmin))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trbVmax))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trbSmax))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trbSmin))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

#pragma endregion


	private: System::Void btnBrowser_Click(System::Object^  sender, System::EventArgs^  e) {
		

		VideoCapture videocap;
		videocap.open(0);				// Capture video from camera
		//videocap.open("filename.mp4");	// Capture video from file
		if (!videocap.isOpened()) {
			MessageBox::Show("Fail to open video");
			_getch();
			return;
		}
		videocap.set(CV_CAP_PROP_FRAME_WIDTH, FRAME_WIDTH);
		videocap.set(CV_CAP_PROP_FRAME_HEIGHT, FRAME_HEIGHT);

		mouseIsDragging = false;
		mouseMove = false;
		rectangleSelected = false;
		
		while (1)
		{

			videocap.read(srcImg);

			
			cvtColor(srcImg, hvsImg, COLOR_BGR2HSV);	// convert ke HSV

			recordHSV_Values(srcImg, hvsImg); // NEW FUNCTION ADDED

			inRange(hvsImg, Scalar(Hmin, Smin, Vmin), Scalar(Hmax, Smax, Vmax), inrImg); // filter dari warna.
			imshow("gambar", inrImg);

			Mat temps;
			inrImg.copyTo(temps);
			vector<vector<cv::Point>> conts;
			vector<Vec4i> hier;
			findContours(temps,conts,hier,CV_RETR_CCOMP,CV_CHAIN_APPROX_SIMPLE);	//cari kontur

			double arearef = 0;
			bool objFound = false;
			if (hier.size() > 0)	// hier: jumlah objek yang terdeteksi setelah di proses
			{
				int obj_qty = hier.size();
				if (obj_qty < Max_obj)	//yg di proses objek < max objek.
				{
					for (int idx = 0; idx >= 0; idx = hier[idx][0]) {
						Moments moms = moments((cv::Mat)conts[idx]);
						double area = moms.m00;
						if (area > MIN_OBJECT_AREA && area < MAX_OBJECT_AREA && area>arearef) // area berada di rangenya
						{
							xm = moms.m10 / area;
							ym = moms.m01 / area;
							objFound = true; // muncul tulisan objek ketemu
							arearef = area; //tampilkan area
						}
						else
						{
							objFound = false;
						}
					}
				}
				if (objFound == true)
				{
					putText(srcImg, "Objek Ketemu!", cv::Point(0, 50), 2, 1, Scalar(0, 0, 255), 2);
					drawObject(xm, ym, srcImg);
				}
			}
			
			if (calibrationMode == true)
			{
				namedWindow("Sumber");
				setMouseCallback("Sumber", clickAndDrag_Rectangle, &srcImg);
				//initiate mouse move and drag to false 
				imshow("Sumber", srcImg);
				
			}
			else
			{
				destroyWindow("Sumber");
			}
			ptbVideo->Image = mat2bmp.Mat2Bimap(srcImg);
			ptbVideo->Refresh();
			if (waitKey(10) == 27)
			{
				break;
			}

		}

	}
	private: System::Void btnProcess_Click(System::Object^  sender, System::EventArgs^  e) {
		if (btnProcess->Text == "Kalibrasi")
		{
			calibrationMode = true;
			btnProcess->Text = "Tutup";
		}
		else
		{
			calibrationMode = false;
			btnProcess->Text = "Kalibrasi";
		}


	}
	private: void recordHSV_Values(cv::Mat frame, cv::Mat hsv_frame) {

		//Nyimpen HSV yang digeser2
		if (mouseMove == false && rectangleSelected == true) {

			//Hapus Value sebelum
			if (H_ROI.size() > 0) H_ROI.clear();
			if (S_ROI.size() > 0) S_ROI.clear();
			if (V_ROI.size() > 0)V_ROI.clear();
			if (rectangleROI.width < 1 || rectangleROI.height < 1) cout << "Jangan garis doang" << endl;
			else {
				for (int i = rectangleROI.x; i < rectangleROI.x + rectangleROI.width; i++) {
					//iterasi x&y
					for (int j = rectangleROI.y; j < rectangleROI.y + rectangleROI.height; j++) {
						//simpen value HSV ke vector
						H_ROI.push_back((int)hsv_frame.at<cv::Vec3b>(j, i)[0]);
						S_ROI.push_back((int)hsv_frame.at<cv::Vec3b>(j, i)[1]);
						V_ROI.push_back((int)hsv_frame.at<cv::Vec3b>(j, i)[2]);
					}
				}
			}
			//Reset select area klo misal mau pilih lagi
			rectangleSelected = false;


			//ngeset min max HSV manual
			if (H_ROI.size() > 0) {
				//min_element&max nya harus dikasih bintang biar ga return itteration
				Hmin = *std::min_element(H_ROI.begin(), H_ROI.end());
				Hmax = *std::max_element(H_ROI.begin(), H_ROI.end());
				cout << "MIN 'H' VALUE: " << Hmin << endl;
				cout << "MAX 'H' VALUE: " << Hmax << endl;
			}
			if (S_ROI.size() > 0) {
				Smin = *std::min_element(S_ROI.begin(), S_ROI.end());
				Smax = *std::max_element(S_ROI.begin(), S_ROI.end());
				cout << "MIN 'S' VALUE: " << Smin << endl;
				cout << "MAX 'S' VALUE: " << Smax << endl;
			}
			if (V_ROI.size() > 0) {
				Vmin = *std::min_element(V_ROI.begin(), V_ROI.end());
				Vmax = *std::max_element(V_ROI.begin(), V_ROI.end());
				cout << "MIN 'V' VALUE: " << Smin << endl;
				cout << "MAX 'V' VALUE: " << Smax << endl;
			}

		}

		if (mouseMove == true) {
			//klo mousenya aktif, nentuin HSV nya pake mouse
			rectangle(frame, initialClickPoint, cv::Point(currentMousePoint.x, currentMousePoint.y), cv::Scalar(0, 255, 0), 1, 8, 0);
		}


	}
	private: void drawObject(int x, int y, Mat &frame) {

		circle(frame, cv::Point(x, y), 20, Scalar(0, 255, 0), 2);
		if (y - 25 > 0)
			line(frame, cv::Point(x, y), cv::Point(x, y - 25), Scalar(0, 255, 0), 2);
		else line(frame, cv::Point(x, y), cv::Point(x, 0), Scalar(0, 255, 0), 2);
		if (y + 25 < FRAME_HEIGHT)
			line(frame, cv::Point(x, y), cv::Point(x, y + 25), Scalar(0, 255, 0), 2);
		else line(frame, cv::Point(x, y), cv::Point(x, FRAME_HEIGHT), Scalar(0, 255, 0), 2);
		if (x - 25 > 0)
			line(frame, cv::Point(x, y), cv::Point(x - 25, y), Scalar(0, 255, 0), 2);
		else line(frame, cv::Point(x, y), cv::Point(0, y), Scalar(0, 255, 0), 2);
		if (x + 25 < FRAME_WIDTH)
			line(frame, cv::Point(x, y), cv::Point(x + 25, y), Scalar(0, 255, 0), 2);
		else line(frame, cv::Point(x, y), cv::Point(FRAME_WIDTH, y), Scalar(0, 255, 0), 2);

		putText(frame, n2str.int2str(x) + "," + n2str.int2str(y), cv::Point(x, y + 30), 1, 1, Scalar(0, 255, 0), 2);

	}
};



}
