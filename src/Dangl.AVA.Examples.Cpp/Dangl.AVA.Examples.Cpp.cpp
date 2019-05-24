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
	if (args->Length != 2) {
		Console::WriteLine(L"Please supply two command line arguments:");
		Console::WriteLine(L"1. Path to a GAEB file to import");
		Console::WriteLine(L"2. Path to the GAEB file to export");
		Console::WriteLine(L"In Visual Studio, you can use these settings:");
		Console::WriteLine(L"\"$(SolutionDir)\\GaebFiles\\GAEBXML_DE.X86\" \"$(SolutionDir)\\GaebExport.X86\"");
		return 1;
	}

	Dangl::AVA::Project^ project = Dangl::AVA::Interop::AvaConverter::ConvertGaebToAva(args[0]);

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

	Dangl::AVA::Interop::AvaConverter::ExportToGaeb(projectToExport, args[1], GaebTargetType::GaebXml);
	Console::WriteLine(args[1]);

	return 0;
}
