﻿/*
 *
 * (C) Copyright IBM Corp.  and others 1998-2013 - All Rights Reserved
 *
 */

#include "LETypes.h"
#include "MorphTables.h"
#include "SubtableProcessor2.h"
#include "NonContextualGlyphSubst.h"
#include "NonContextualGlyphSubstProc2.h"
#include "SegmentArrayProcessor2.h"
#include "LEGlyphStorage.h"
#include "LESwaps.h"

U_NAMESPACE_BEGIN

UOBJECT_DEFINE_RTTI_IMPLEMENTATION(SegmentArrayProcessor2)

SegmentArrayProcessor2::SegmentArrayProcessor2()
{
}

SegmentArrayProcessor2::SegmentArrayProcessor2(const LEReferenceTo<MorphSubtableHeader2> &morphSubtableHeader, LEErrorCode &success)
  : NonContextualGlyphSubstitutionProcessor2(morphSubtableHeader, success)
{
  const LEReferenceTo<NonContextualGlyphSubstitutionHeader2> header(morphSubtableHeader, success);
  segmentArrayLookupTable = LEReferenceTo<SegmentArrayLookupTable>(morphSubtableHeader,  success, &header->table); // don't parent to 'header' as it is on the stack
}

SegmentArrayProcessor2::~SegmentArrayProcessor2()
{
}

void SegmentArrayProcessor2::process(LEGlyphStorage &glyphStorage, LEErrorCode &success)
{
    const LookupSegment *segments = segmentArrayLookupTable->segments;
    le_int32 glyphCount = glyphStorage.getGlyphCount();
    le_int32 glyph;

    for (glyph = 0; glyph < glyphCount; glyph += 1) {
        LEGlyphID thisGlyph = glyphStorage[glyph];
        const LookupSegment *lookupSegment = segmentArrayLookupTable->lookupSegment(segmentArrayLookupTable, segments, thisGlyph, success);

        if (lookupSegment != NULL)  {
            TTGlyphID firstGlyph = SWAPW(lookupSegment->firstGlyph);
            le_int16  offset = SWAPW(lookupSegment->value);

            if (offset != 0) {
              TTGlyphID  *glyphArray = (TTGlyphID *) ((char *) subtableHeader.getAliasRAW() + offset);
                TTGlyphID   newGlyph   = SWAPW(glyphArray[LE_GET_GLYPH(thisGlyph) - firstGlyph]);
                
                glyphStorage[glyph] = LE_SET_GLYPH(thisGlyph, newGlyph);
            } 
        }
    }
}
 
U_NAMESPACE_END
