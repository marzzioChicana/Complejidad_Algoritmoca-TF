#pragma once
#include "cosas.h"
namespace PFComplejidad {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data; 
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Fromulario
	/// </summary>
	public ref class Fromulario : public System::Windows::Forms::Form
	{
	public:
		Fromulario(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			grafo = new GrafoEstaciones();
			grafo->leer();
			grafo->mostrarListaDeAdyasencia();
			grafo->leercoords();
			mapa = gcnew Bitmap("mapa.png");
			canvas = panel1->CreateGraphics();
			grafo->actualizarCombobox(cbPartida, cbDestino, cbEstacionesND);
			espacioBuffer = BufferedGraphicsManager::Current;
			buffer = espacioBuffer->Allocate(canvas, this->ClientRectangle);
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Fromulario()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Panel^ panel1;
	private: System::ComponentModel::IContainer^ components;
	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>

		GrafoEstaciones* grafo;
		Bitmap^ mapa;
	private: System::Windows::Forms::Timer^ timer1;
	private: System::Windows::Forms::ComboBox^ cbPartida;
	private: System::Windows::Forms::ComboBox^ cbDestino;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
		   BufferedGraphics^ buffer;
		   BufferedGraphicsContext^ espacioBuffer;
	private: System::Windows::Forms::Label^ label3;

	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::ComboBox^ cbEstacionesND;

	private: System::Windows::Forms::Button^ btnAdd;
	private: System::Windows::Forms::RichTextBox^ txtRuta;
	private: System::Windows::Forms::RichTextBox^ txtEstacionesND;
	private: System::Windows::Forms::Label^ labelTiempo;
	private: System::Windows::Forms::PictureBox^ pictureBox1;



		   Graphics^ canvas;
#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(Fromulario::typeid));
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->cbPartida = (gcnew System::Windows::Forms::ComboBox());
			this->cbDestino = (gcnew System::Windows::Forms::ComboBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->cbEstacionesND = (gcnew System::Windows::Forms::ComboBox());
			this->btnAdd = (gcnew System::Windows::Forms::Button());
			this->txtRuta = (gcnew System::Windows::Forms::RichTextBox());
			this->txtEstacionesND = (gcnew System::Windows::Forms::RichTextBox());
			this->labelTiempo = (gcnew System::Windows::Forms::Label());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// panel1
			// 
			this->panel1->Location = System::Drawing::Point(312, 12);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(992, 720);
			this->panel1->TabIndex = 0;
			this->panel1->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Fromulario::panel1_Paint);
			// 
			// timer1
			// 
			this->timer1->Enabled = true;
			this->timer1->Interval = 500;
			this->timer1->Tick += gcnew System::EventHandler(this, &Fromulario::timer1_Tick);
			// 
			// cbPartida
			// 
			this->cbPartida->FormattingEnabled = true;
			this->cbPartida->Location = System::Drawing::Point(67, 107);
			this->cbPartida->Name = L"cbPartida";
			this->cbPartida->Size = System::Drawing::Size(179, 21);
			this->cbPartida->TabIndex = 1;
			this->cbPartida->SelectedIndexChanged += gcnew System::EventHandler(this, &Fromulario::cbPartida_SelectedIndexChanged);
			// 
			// cbDestino
			// 
			this->cbDestino->FormattingEnabled = true;
			this->cbDestino->Location = System::Drawing::Point(67, 169);
			this->cbDestino->Name = L"cbDestino";
			this->cbDestino->Size = System::Drawing::Size(179, 21);
			this->cbDestino->TabIndex = 2;
			this->cbDestino->SelectedIndexChanged += gcnew System::EventHandler(this, &Fromulario::cbDestino_SelectedIndexChanged);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(122, 79);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(71, 25);
			this->label1->TabIndex = 3;
			this->label1->Text = L"partida";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->Location = System::Drawing::Point(122, 141);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(75, 25);
			this->label2->TabIndex = 4;
			this->label2->Text = L"destino";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label3->Location = System::Drawing::Point(37, 29);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(241, 25);
			this->label3->TabIndex = 5;
			this->label3->Text = L"FranceTravelerAssistance";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label4->Location = System::Drawing::Point(131, 217);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(52, 25);
			this->label4->TabIndex = 7;
			this->label4->Text = L"Ruta";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label5->Location = System::Drawing::Point(40, 425);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(238, 25);
			this->label5->TabIndex = 9;
			this->label5->Text = L"Estaciones no disponibles";
			// 
			// cbEstacionesND
			// 
			this->cbEstacionesND->FormattingEnabled = true;
			this->cbEstacionesND->Location = System::Drawing::Point(32, 455);
			this->cbEstacionesND->Name = L"cbEstacionesND";
			this->cbEstacionesND->Size = System::Drawing::Size(166, 21);
			this->cbEstacionesND->TabIndex = 8;
			// 
			// btnAdd
			// 
			this->btnAdd->Location = System::Drawing::Point(204, 453);
			this->btnAdd->Name = L"btnAdd";
			this->btnAdd->Size = System::Drawing::Size(82, 23);
			this->btnAdd->TabIndex = 11;
			this->btnAdd->Text = L"Añadir";
			this->btnAdd->UseVisualStyleBackColor = true;
			this->btnAdd->Click += gcnew System::EventHandler(this, &Fromulario::btnAdd_Click);
			// 
			// txtRuta
			// 
			this->txtRuta->Location = System::Drawing::Point(45, 245);
			this->txtRuta->Name = L"txtRuta";
			this->txtRuta->Size = System::Drawing::Size(222, 143);
			this->txtRuta->TabIndex = 12;
			this->txtRuta->Text = L"";
			// 
			// txtEstacionesND
			// 
			this->txtEstacionesND->Enabled = false;
			this->txtEstacionesND->Location = System::Drawing::Point(45, 482);
			this->txtEstacionesND->Name = L"txtEstacionesND";
			this->txtEstacionesND->Size = System::Drawing::Size(222, 124);
			this->txtEstacionesND->TabIndex = 13;
			this->txtEstacionesND->Text = L"";
			this->txtEstacionesND->TextChanged += gcnew System::EventHandler(this, &Fromulario::txtEstacionesND_TextChanged);
			// 
			// labelTiempo
			// 
			this->labelTiempo->AutoSize = true;
			this->labelTiempo->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->labelTiempo->Location = System::Drawing::Point(62, 391);
			this->labelTiempo->Name = L"labelTiempo";
			this->labelTiempo->Size = System::Drawing::Size(0, 25);
			this->labelTiempo->TabIndex = 14;
			// 
			// pictureBox1
			// 
			this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.Image")));
			this->pictureBox1->Location = System::Drawing::Point(42, 612);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(230, 121);
			this->pictureBox1->TabIndex = 15;
			this->pictureBox1->TabStop = false;
			// 
			// Fromulario
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1317, 743);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->labelTiempo);
			this->Controls->Add(this->txtEstacionesND);
			this->Controls->Add(this->txtRuta);
			this->Controls->Add(this->btnAdd);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->cbEstacionesND);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->cbDestino);
			this->Controls->Add(this->cbPartida);
			this->Controls->Add(this->panel1);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"Fromulario";
			this->Text = L"Fromulario";
			this->Load += gcnew System::EventHandler(this, &Fromulario::Fromulario_Load);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Fromulario::Fromulario_KeyDown);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void Fromulario_Load(System::Object^ sender, System::EventArgs^ e) {

	}
	private: System::Void panel1_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
		//Rectangle areavisible(0, 0, mapa->Width, mapa->Height);
		//canvas->DrawImage(mapa, 0, 0, areavisible, GraphicsUnit::Pixel);
	}
	private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {
		Rectangle areavisible(0, 0, mapa->Width, mapa->Height);
		buffer->Graphics->DrawImage(mapa, 0, 0, mapa->Width, mapa->Height);
		grafo->graficar(buffer->Graphics,cbPartida, cbDestino);
		buffer->Render(canvas);

	}
	private: System::Void Fromulario_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		 
	}
	private: System::Void cbPartida_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
		grafo->dijkstra2(cbPartida, cbDestino, txtRuta, labelTiempo);
	}
	private: System::Void cbDestino_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
		grafo->dijkstra2(cbPartida, cbDestino, txtRuta, labelTiempo);
	}
	private: System::Void btnAdd_Click(System::Object^ sender, System::EventArgs^ e) {
		grafo->eliminarEstacion(cbEstacionesND, txtEstacionesND);
	}
	private: System::Void txtEstacionesND_TextChanged(System::Object^ sender, System::EventArgs^ e) {
		grafo->dijkstra2(cbPartida, cbDestino, txtRuta, labelTiempo);
	}
};
}
