
// WeatherByMaxDoc.h : interface of the CWeatherByMaxDoc class
//


#pragma once
#include <vector>
using namespace std;

class CWeatherByMaxDoc : public CDocument
{
protected: // create from serialization only
	CWeatherByMaxDoc() noexcept;
	DECLARE_DYNCREATE(CWeatherByMaxDoc)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CWeatherByMaxDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
private:
	vector <int> TempH; //vector to store hi temp
	vector <int> TempL; //vector to store low temp
	CString Location;
	int days;

	//Think about making new vector if days want to be read in
	//NOTE: Vectors used originally as I wanted a way to read in data indefinetly
	//as they offer a add function and dont set a length like an array
	//But CArray could easily be used in their place and offers all the same benifits

public:
	//getter & setter public functions to access data in view
	int TempHGetter(int n) { return TempH[n]; };
	int TempLGetter(int n) { return TempL[n]; };
	CString LocationGetter() { return Location; };
	int LengthGetter() { return days; };
	bool dataRead{ false }; //bool for if data is read
	~CWeatherByMaxDoc() { TempH.clear(); TempL.clear(); }; //destructor to deallocate memory
};
