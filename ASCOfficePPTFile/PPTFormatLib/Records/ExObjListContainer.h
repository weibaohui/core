#pragma once
#include "../Reader/Records.h"

class CRecordExObjListContainer : public CRecordsContainer
{
public:
	
	CRecordExObjListContainer()
	{
	}

	~CRecordExObjListContainer()
	{
	}

	virtual void ReadFromStream(SRecordHeader & oHeader, POLE::Stream* pStream)
	{
		CRecordsContainer::ReadFromStream(oHeader, pStream);
	}
};