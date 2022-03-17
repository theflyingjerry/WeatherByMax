
// WeatherByMaxDoc.cpp : implementation of the CWeatherByMaxDoc class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "WeatherByMax.h"
#endif

#include "WeatherByMaxDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CWeatherByMaxDoc

IMPLEMENT_DYNCREATE(CWeatherByMaxDoc, CDocument)

BEGIN_MESSAGE_MAP(CWeatherByMaxDoc, CDocument)
END_MESSAGE_MAP()


// CWeatherByMaxDoc construction/destruction

CWeatherByMaxDoc::CWeatherByMaxDoc() noexcept
{
	// TODO: add one-time construction code here

}

CWeatherByMaxDoc::~CWeatherByMaxDoc()
{
}

BOOL CWeatherByMaxDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CWeatherByMaxDoc serialization - Reading and writing data to/ from files

void CWeatherByMaxDoc::Serialize(CArchive& ar)
{
	CObject::Serialize(ar); //needed for serialization

	//Section to write to file
	if (ar.IsStoring())
	{
		CString C; //Template Cstring that can be modified as needed 
		ar.WriteString(Location); //Write weather location to file
		ar.WriteString(_T("\n")); //Write new line 
		C.Format(_T("%d\n"), days); //Format string to include number of days ie length of vector
		ar.WriteString(C); //write string to file
		for (int i = 0; i < days; i++) {  //loop over data
			C.Format(_T("%d, %d\n"),TempH[i], TempL[i]); //format string to be in from "hi, low"
			ar.WriteString(C); //write string to file
		}
	}
	else //reading from file
	{
		try {
			CString C; //holder string
			ar.ReadString(Location); //read in first line of text and store to variable location
			ar.ReadString(C); //read second line of text and store to variable c
			days = _ttoi(C); //convert c from string to int and set as days
			for (int i = 0; i < days; i++) { //loop for number of days
					ar.ReadString(C); //read line of text
					CString tok = _T(""); //second holder string
					int j = 0; //iterator
					//Loop over string C and break into pieces at comma and store in tok string
					while (AfxExtractSubString(tok, C, j, ',')) {
						if (j == 0) { //ie first half of string ie high temp
							TempH.push_back(_ttoi(tok)); //add to vector as int
						}
						else if (j == 1) { //second half of string ie low temp
							TempL.push_back(_ttoi(tok)); //add to vector as int
						}
						j++; //iterate
					}
				}
			}	
			catch (CArchiveException* e) { //catch if there is an error endOfFile is ignored
				if (e->m_cause == CArchiveException::endOfFile) {
					e->Delete();
				}
				else {
					AfxMessageBox(_T("Incorrect file type"));
					throw;	
				}
			}
		dataRead = true; //set bool as true if read successfully
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CWeatherByMaxDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CWeatherByMaxDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data.
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CWeatherByMaxDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CWeatherByMaxDoc diagnostics

#ifdef _DEBUG
void CWeatherByMaxDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CWeatherByMaxDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CWeatherByMaxDoc commands
