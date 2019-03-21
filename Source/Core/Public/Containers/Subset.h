// Copyright 2019 Simon Kim All Rights Reserved.

#ifndef RADON_SUBSET_H
#define RADON_SUBSET_H

#include "RadonCore.h"

template <typename T, typename Allocator>
class TList;

namespace Radon
{
	template <template <typename, typename> typename Superset, typename T, typename Allocator>
	class RADON_API TSubset
	{
		typedef TSubset<Superset, T, Allocator> MyType;

	public:
		typedef T											ElementType;
		typedef Allocator									AllocatorType;
		typedef Superset<ElementType, AllocatorType>		SupersetType;
		typedef TList<ElementType&, AllocatorType>			ReferenceContainerType;

	public:

		// Constructors
		TSubset(SupersetType &superset,
				IndexArrayType &&indicies);

		// Destructors
		~TSubset();

		ElementType& operator[](TIndex index);
		ElementType& At(TIndex index);
		const ElementType& operator[](TIndex index) const;
		const ElementType& At(TIndex index);

		TIndex GetRealIndex(TIndex myIndex) const;

		TSize Size() const;

		SupersetType& GetSuperset();
		const SupersetType& GetSuperset() const;

	private:
		SupersetType &m_superset;
		ReferenceContainerType m_refs;
	};
}

#endif