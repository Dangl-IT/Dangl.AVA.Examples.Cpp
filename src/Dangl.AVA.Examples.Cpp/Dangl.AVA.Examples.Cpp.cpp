// Dangl.AVA.Examples.Cpp.cpp : main project file.

#include "stdafx.h"
#include <iostream>

using namespace Dangl::AVA::Interop;
using namespace System;
using namespace Dangl::AVA;
using namespace Dangl::AVA::Contents;
using namespace Dangl::AVA::Extensions;
using namespace Dangl::AVA::Contents::ServiceSpecificationContents;

int main(array<System::String ^> ^args)
{
	char inputGaebFile[] = "C:\\Users\\Georg\\Git\\Dangl.AVA.Examples.Cpp\\GaebFiles\\GAEBXML_DE.X86";
	char outputGaebFile[] = "C:\\Users\\Georg\\Git\\Dangl.AVA.Examples.Cpp\\GaebExport.X86";

	Dangl::AVA::Project^ project = Dangl::AVA::Interop::AvaConverter::ConvertGaebToAva(gcnew System::String(inputGaebFile));

	array<Position^> ^positions = AvaConverter::GetPositionsInProject(project);

	Console::WriteLine(L"Printing positions in imported GAEB file:");
	Console::WriteLine(L"********************");
	for (int i = 0; i < positions->Length; i++) {
		Console::WriteLine(positions[i]->ItemNumber->StringRepresentation);
		Console::WriteLine(positions[i]->ShortText);
		Console::WriteLine(positions[i]->TotalPrice);
		Console::WriteLine(L"********************");
	}

	Console::WriteLine(L"Creating new GAEB file:");
	GaebTargetType targetType = GaebTargetType::GaebXml;
	Project^ projectToExport = gcnew Project();
	ServiceSpecification^ servSpec = gcnew ServiceSpecification();
	servSpec->ExchangePhase = ExchangePhase::Grant;
	projectToExport->ServiceSpecifications->Add(servSpec);

	Position^ position = gcnew Position();
	position->ShortText = "C++ Position";
	position->ItemNumber->StringRepresentation = "01";
	Dangl::AVA::Contents::ServiceSpecificationContents::PositionExtensions::SetUnitPrice(position, *gcnew System::Decimal(12));
	Dangl::AVA::Contents::ServiceSpecificationContents::PositionExtensions::SetQuantity(position, *gcnew System::Decimal(5));
	servSpec->Elements->Add(position);

	Dangl::AVA::Interop::AvaConverter::ExportToGaeb(projectToExport, gcnew System::String(outputGaebFile), GaebTargetType::GaebXml);
	Console::WriteLine(gcnew System::String(outputGaebFile));

	return 0;
}
