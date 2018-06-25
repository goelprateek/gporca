//---------------------------------------------------------------------------
//	Greenplum Database
//	Copyright (C) 2012 EMC Corp.
//
//	@filename:
//		CMDRequest.h
//
//	@doc:
//		Class for a representing MD requests
//---------------------------------------------------------------------------



#ifndef GPMD_CMDRequest_H
#define GPMD_CMDRequest_H

#include "gpos/base.h"
#include "gpos/common/CRefCount.h"
#include "gpos/common/CDynamicPtrArray.h"

#include "naucrates/md/CSystemId.h"
#include "naucrates/md/IMDType.h"
#include "naucrates/md/IMDFunction.h"

namespace gpmd
{
	using namespace gpos;


	//--------------------------------------------------------------------------
	//	@class:
	//		CMDRequest
	//
	//	@doc:
	//		Class for representing MD requests
	//
	//--------------------------------------------------------------------------
	class CMDRequest : public CRefCount
	{
	public:
		// fwd decl
		struct SMDTypeRequest;
		struct SMDFuncRequest;

		// array of type requests
		typedef CDynamicPtrArray<SMDTypeRequest, CleanupDelete> MDTypeRequestPtrArray;

		//---------------------------------------------------------------------------
		//	@class:
		//		SMDTypeRequest
		//
		//	@doc:
		//		Struct for representing requests for types metadata
		//
		//---------------------------------------------------------------------------
		struct SMDTypeRequest
		{
			// system id
			CSystemId m_sysid;

			// type info
			IMDType::ETypeInfo m_type_info;

			// ctor
			SMDTypeRequest(CSystemId sysid, IMDType::ETypeInfo type_info)
				: m_sysid(sysid), m_type_info(type_info)
			{
			}
		};

	private:
		// memory pool
		IMemoryPool *m_memory_pool;

		// array of mdids
		MdidPtrArray *m_mdid_array;

		// type info requests
		MDTypeRequestPtrArray *m_mdtype_request_array;

		// serialize system id
		CWStringDynamic *GetStrRepr(CSystemId sysid);

		// private copy ctor
		CMDRequest(const CMDRequest &);

	public:
		// ctor
		CMDRequest(IMemoryPool *memory_pool,
				   MdidPtrArray *mdid_array,
				   MDTypeRequestPtrArray *mdtype_request_array);

		// ctor: type request only
		CMDRequest(IMemoryPool *memory_pool, SMDTypeRequest *md_type_request);

		// dtor
		virtual ~CMDRequest();

		// accessors

		// array of mdids
		MdidPtrArray *
		GetMdIdArray() const
		{
			return m_mdid_array;
		}

		// array of type info requests
		MDTypeRequestPtrArray *
		GetMDTypeRequestArray() const
		{
			return m_mdtype_request_array;
		}

		// serialize request in DXL format
		virtual void Serialize(gpdxl::CXMLSerializer *xml_serializer);
	};
}  // namespace gpmd

#endif  // !GPMD_CMDRequest_H

// EOF
