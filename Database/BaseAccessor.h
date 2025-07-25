#pragma once

template<typename TRecordType>
class CBaseAccessor {
public:
	TRecordType m_recRecord;
public:
	TRecordType& GetRecord()
	{
		return this->m_recRecord;
	}
	void SetRecord(const TRecordType& rec)
	{
		this->m_recRecord = rec;
	}
};