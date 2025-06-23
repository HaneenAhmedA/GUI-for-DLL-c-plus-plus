#pragma once
#include "dll.gui.h"
#include <msclr/marshal_cppstd.h>

namespace dllgui {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		DLL* list1;

		MyForm(void)
		{
			InitializeComponent();
			list1 = new DLL();
		}

	protected:
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::RichTextBox^ richTextBoxOutput;
	private: System::Windows::Forms::TextBox^ inputBox1;
	private: System::Windows::Forms::Button^ insertBtn1;
	private: System::Windows::Forms::Button^ buttonDelete;
	private: System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		   void InitializeComponent(void)
		   {
			   this->richTextBoxOutput = (gcnew System::Windows::Forms::RichTextBox());
			   this->inputBox1 = (gcnew System::Windows::Forms::TextBox());
			   this->insertBtn1 = (gcnew System::Windows::Forms::Button());
			   this->buttonDelete = (gcnew System::Windows::Forms::Button());
			   this->SuspendLayout();
			   // 
			   // richTextBoxOutput
			   // 
			   this->richTextBoxOutput->Location = System::Drawing::Point(59, 194);
			   this->richTextBoxOutput->Name = L"richTextBoxOutput";
			   this->richTextBoxOutput->Size = System::Drawing::Size(499, 187);
			   this->richTextBoxOutput->TabIndex = 2;
			   this->richTextBoxOutput->Text = L"";
			   // 
			   // inputBox1
			   // 
			   this->inputBox1->Location = System::Drawing::Point(104, 30);
			   this->inputBox1->Name = L"inputBox1";
			   this->inputBox1->Size = System::Drawing::Size(394, 24);
			   this->inputBox1->TabIndex = 3;
			   // 
			   // insertBtn1
			   // 
			   this->insertBtn1->Location = System::Drawing::Point(621, 15);
			   this->insertBtn1->Name = L"insertBtn1";
			   this->insertBtn1->Size = System::Drawing::Size(222, 39);
			   this->insertBtn1->TabIndex = 4;
			   this->insertBtn1->Text = L"Insert to List 1";
			   this->insertBtn1->UseVisualStyleBackColor = true;
			   this->insertBtn1->Click += gcnew System::EventHandler(this, &MyForm::insertBtn1_Click);
			   // 
			   // buttonDelete
			   // 
			   this->buttonDelete->Location = System::Drawing::Point(626, 77);
			   this->buttonDelete->Name = L"buttonDelete";
			   this->buttonDelete->Size = System::Drawing::Size(216, 32);
			   this->buttonDelete->TabIndex = 5;
			   this->buttonDelete->Text = L"Delete at Index";
			   this->buttonDelete->UseVisualStyleBackColor = true;
			   this->buttonDelete->Click += gcnew System::EventHandler(this, &MyForm::buttonDelete_Click);
			   // 
			   // MyForm
			   // 
			   this->AutoScaleDimensions = System::Drawing::SizeF(7, 16);
			   this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			   this->ClientSize = System::Drawing::Size(1010, 452);
			   this->Controls->Add(this->buttonDelete);
			   this->Controls->Add(this->insertBtn1);
			   this->Controls->Add(this->inputBox1);
			   this->Controls->Add(this->richTextBoxOutput);
			   this->Name = L"MyForm";
			   this->Text = L"MyForm";
			   this->ResumeLayout(false);
			   this->PerformLayout();

		   }
#pragma endregion

	private: System::Void insertBtn1_Click(System::Object^ sender, System::EventArgs^ e)
	{
		System::String^ str = inputBox1->Text;
		std::string nativeStr = msclr::interop::marshal_as<std::string>(str);

		// Insert into the linked list
		for (int i = 0; i < nativeStr.length(); i++) {
			list1->insertion(nativeStr[i], list1->StringLength()); // insert at the end
		}

		// Display result in richTextBoxOutput
		Node* current = list1->getHead(); // You must define getHead() in your DLL class
		std::string result;
		while (current != nullptr) {
			result += current->info;
			current = current->next;
		}

		richTextBoxOutput->Text = gcnew System::String(result.c_str());
	}
	private: System::Void buttonDelete_Click(System::Object^ sender, System::EventArgs^ e) {
		try {
			// Use inputBox1 for deletion input
			int index = Int32::Parse(inputBox1->Text);  // reuse the same textbox
			list1->deletion(index); // call DLL function

			// Display the updated list
			Node* current = list1->getHead();  // assumes getHead() exists
			std::string result;
			while (current != nullptr) {
				result += current->info;
				current = current->next;
			}

			richTextBoxOutput->Text = gcnew System::String(result.c_str());

			inputBox1->Clear(); // Clear input box
		}
		catch (Exception^ ex) {
			MessageBox::Show("Please enter a valid number.");
		}
	}
}; // ✅ This closes the class MyForm

} // ✅ This closes the namespace dllgui
