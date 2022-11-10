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
			grafo->actualizarCombobox(cbPartida, cbDestino);
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

		   Graphics^ canvas;
#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->cbPartida = (gcnew System::Windows::Forms::ComboBox());
			this->cbDestino = (gcnew System::Windows::Forms::ComboBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// panel1
			// 
			this->panel1->Location = System::Drawing::Point(312, 12);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(1162, 720);
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
			this->cbPartida->Location = System::Drawing::Point(123, 65);
			this->cbPartida->Name = L"cbPartida";
			this->cbPartida->Size = System::Drawing::Size(121, 21);
			this->cbPartida->TabIndex = 1;
			this->cbPartida->SelectedIndexChanged += gcnew System::EventHandler(this, &Fromulario::cbPartida_SelectedIndexChanged);
			// 
			// cbDestino
			// 
			this->cbDestino->FormattingEnabled = true;
			this->cbDestino->Location = System::Drawing::Point(123, 127);
			this->cbDestino->Name = L"cbDestino";
			this->cbDestino->Size = System::Drawing::Size(121, 21);
			this->cbDestino->TabIndex = 2;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(45, 68);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(39, 13);
			this->label1->TabIndex = 3;
			this->label1->Text = L"partida";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(45, 130);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(41, 13);
			this->label2->TabIndex = 4;
			this->label2->Text = L"destino";
			// 
			// Fromulario
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1486, 743);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->cbDestino);
			this->Controls->Add(this->cbPartida);
			this->Controls->Add(this->panel1);
			this->Name = L"Fromulario";
			this->Text = L"Fromulario";
			this->Load += gcnew System::EventHandler(this, &Fromulario::Fromulario_Load);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Fromulario::Fromulario_KeyDown);
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
		grafo->dijkstra(cbPartida);
	}
};
}
