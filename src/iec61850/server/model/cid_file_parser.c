/*
 * cid_file_parser.c
 *
 * Copyright 2024 Zhang Bin
 *
 * This file is part of libIEC61850.
 *
 * libIEC61850 is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * libIEC61850 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libIEC61850.  If not, see <http://www.gnu.org/licenses/>.
 *
 * See COPYING file for the complete license text.
 */

#include "iec61850_dynamic_model.h"
#include "iec61850_cid_file_parser.h"
#include "libiec61850_platform_includes.h"
#include "mxml.h"
#include "map.h"

DataAttributeDefinition*
CidFileParser_parseDADefinition(mxml_node_t* node)
{
    const char* name = mxmlElementGetAttr(node, "name");
    const char* bType = mxmlElementGetAttr(node, "bType");
    const char* fcString = mxmlElementGetAttr(node, "fc");

    DataAttributeDefinition* daDefinition = (DataAttributeDefinition*) GLOBAL_MALLOC(sizeof(DataAttributeDefinition));

    if (name == NULL) {
        if (DEBUG_IED_SERVER)
            printf("IED_SERVER: DataAttributeDefinition attribute name is missing!\n");
        GLOBAL_FREEMEM(daDefinition);
        return NULL;
    }
    daDefinition->name = StringUtils_copyString(name);

    if (bType == NULL) {
        if (DEBUG_IED_SERVER)
            printf("IED_SERVER: DataAttributeDefinition attribute bType is missing!\n");
        GLOBAL_FREEMEM(daDefinition);
        return NULL;
    }
    if (StringUtils_compareStrings(bType, "BOOLEAN") == 0) {
        daDefinition->attributeType = IEC61850_BOOLEAN;
    } else if (StringUtils_compareStrings(bType, "INT8") == 0) {
        daDefinition->attributeType = IEC61850_INT8;
    } else if (StringUtils_compareStrings(bType, "INT16") == 0) {
        daDefinition->attributeType = IEC61850_INT16;
    } else if (StringUtils_compareStrings(bType, "INT32") == 0) {
        daDefinition->attributeType = IEC61850_INT32;
    } else if (StringUtils_compareStrings(bType, "INT64") == 0) {
        daDefinition->attributeType = IEC61850_INT64;
    } else if (StringUtils_compareStrings(bType, "INT128") == 0) {
        daDefinition->attributeType = IEC61850_INT128;
    } else if (StringUtils_compareStrings(bType, "INT8U") == 0) {
        daDefinition->attributeType = IEC61850_INT8U;
    } else if (StringUtils_compareStrings(bType, "INT16U") == 0) {
        daDefinition->attributeType = IEC61850_INT16U;
    } else if (StringUtils_compareStrings(bType, "INT24U") == 0) {
        daDefinition->attributeType = IEC61850_INT24U;
    } else if (StringUtils_compareStrings(bType, "INT32U") == 0) {
        daDefinition->attributeType = IEC61850_INT32U;
    } else if (StringUtils_compareStrings(bType, "FLOAT32") == 0) {
        daDefinition->attributeType = IEC61850_FLOAT32;
    } else if (StringUtils_compareStrings(bType, "FLOAT64") == 0) {
        daDefinition->attributeType = IEC61850_FLOAT64;
    } else if (StringUtils_compareStrings(bType, "Enum") == 0) {
        daDefinition->attributeType = IEC61850_ENUMERATED;
    } else if (StringUtils_compareStrings(bType, "Dbpos") == 0) {
        daDefinition->attributeType = IEC61850_CODEDENUM;
    } else if (StringUtils_compareStrings(bType, "Check") == 0) {
        daDefinition->attributeType = IEC61850_CHECK;
    } else if (StringUtils_compareStrings(bType, "Tcmd") == 0) {
        daDefinition->attributeType = IEC61850_CODEDENUM;
    } else if (StringUtils_compareStrings(bType, "Octet64") == 0) {
        daDefinition->attributeType = IEC61850_OCTET_STRING_64;
    } else if (StringUtils_compareStrings(bType, "Quality") == 0) {
        daDefinition->attributeType = IEC61850_QUALITY;
    } else if (StringUtils_compareStrings(bType, "Timestamp") == 0) {
        daDefinition->attributeType = IEC61850_TIMESTAMP;
    } else if (StringUtils_compareStrings(bType, "Currency") == 0) {
        daDefinition->attributeType = IEC61850_CURRENCY;
    } else if (StringUtils_compareStrings(bType, "VisString32") == 0) {
        daDefinition->attributeType = IEC61850_VISIBLE_STRING_32;
    } else if (StringUtils_compareStrings(bType, "VisString64") == 0) {
        daDefinition->attributeType = IEC61850_VISIBLE_STRING_64;
    } else if (StringUtils_compareStrings(bType, "VisString65") == 0) {
        daDefinition->attributeType = IEC61850_VISIBLE_STRING_65;
    } else if (StringUtils_compareStrings(bType, "VisString129") == 0) {
        daDefinition->attributeType = IEC61850_VISIBLE_STRING_129;
    } else if (StringUtils_compareStrings(bType, "ObjRef") == 0) {
        daDefinition->attributeType = IEC61850_VISIBLE_STRING_129;
    } else if (StringUtils_compareStrings(bType, "VisString255") == 0) {
        daDefinition->attributeType = IEC61850_VISIBLE_STRING_255;
    } else if (StringUtils_compareStrings(bType, "Unicode255") == 0) {
        daDefinition->attributeType = IEC61850_UNICODE_STRING_255;
    } else if (StringUtils_compareStrings(bType, "OptFlds") == 0) {
        daDefinition->attributeType = IEC61850_OPTFLDS;
    } else if (StringUtils_compareStrings(bType, "TrgOps") == 0) {
        daDefinition->attributeType = IEC61850_TRGOPS;
    } else if (StringUtils_compareStrings(bType, "EntryID") == 0) {
        daDefinition->attributeType = IEC61850_OCTET_STRING_8;
    } else if (StringUtils_compareStrings(bType, "EntryTime") == 0) {
        daDefinition->attributeType = IEC61850_ENTRY_TIME;
    } else if (StringUtils_compareStrings(bType, "PhyComAddr") == 0) {
        daDefinition->attributeType = IEC61850_PHYCOMADDR;
    } else if (StringUtils_compareStrings(bType, "Struct") == 0) {
        daDefinition->attributeType = IEC61850_CONSTRUCTED;
    } else {
        if (DEBUG_IED_SERVER)
            printf("IED_SERVER: Unknown DataAttributeDefinition attribute bType: %s!\n", bType);
        GLOBAL_FREEMEM(daDefinition);
        return NULL;
    }

    if (fcString!= NULL) {
        daDefinition->fc = FunctionalConstraint_fromString(fcString);
    }

}

DataObjectDefinition*
CidFileParser_parseDODefinition(mxml_node_t* doTypeNode)
{
    char* doId = mxmlElementGetAttr(doTypeNode, "id");
    DataObject* dataObject = DataObject_create(doId, NULL, 0);
    mxml_node_t* childNode = mxmlFindElement(doTypeNode, NULL, "DA", NULL, NULL, MXML_DESCEND_ALL);
    return dataObject;
}

LogicalNodeDefinition*
CidFileParser_parseLNDefinition(mxml_node_t* lnTypeNode)
{
    mxml_node_t* childNode = mxmlFindElement(lnTypeNode, NULL, "LNT", NULL, NULL, MXML_DESCEND_ALL);

    while (childNode!= NULL) {
        char* lnClass = mxmlElementGetAttr(childNode, "lnClass");

    }
}

IedModel*
CidFileParser_createModelFromCidFileEx(const char* filename)
{
    FILE* cidFile = fopen(filename, "r");

    if (cidFile == NULL) {
        if (DEBUG_IED_SERVER)
            printf("IED_SERVER: Error opening cid file!\n");
        return NULL;
    }

    IedModel* model = CidFileParser_createModelFromCidFile(cidFile);

    fclose(cidFile);

    return model;
}

IedModel*
CidFileParser_createModelFromCidFile(FILE* fileHandle)
{
    mxml_node_t* xmlDoc = mxmlLoadFile(NULL, NULL, fileHandle);
    Map daDefinitionMap = Map_create();
    Map doDefinitionMap = Map_create();
    Map lnDefinitionMap = Map_create();

    if (xmlDoc == NULL) {
        if (DEBUG_IED_SERVER)
            printf("IED_SERVER: Error parsing cid file!\n");
        return NULL;
    }

    mxml_node_t* sclNode = mxmlGetLastChild(xmlDoc);
    if (sclNode == NULL) {
        if (DEBUG_IED_SERVER)
            printf("IED_SERVER: Error finding SCL section in configuration file!\n");
        return NULL;
    }

    // parse the DataTypeTemplates Section
    mxml_node_t* dataTypeTemplatesNode = mxmlFindElement(sclNode, sclNode, "DataTypeTemplates", NULL, NULL, MXML_DESCEND_FIRST);

    if (dataTypeTemplatesNode == NULL) {
        if (DEBUG_IED_SERVER)
            printf("IED_SERVER: Error finding DataTypeTemplates section in configuration file!\n");
        mxmlDelete(xmlDoc);
        return NULL;
    }

    // parse all dataAttribute Definitions and store them in a map
    mxml_node_t* daDefinitionNode = mxmlFindElement(dataTypeTemplatesNode, dataTypeTemplatesNode, "DAType", NULL, NULL, MXML_DESCEND_ALL);
    while (daDefinitionNode != NULL) {
        const char* daTypeId = mxmlElementGetAttr(daDefinitionNode, "id");
        if (daTypeId == NULL) {
            if (DEBUG_IED_SERVER)
                printf("IED_SERVER: Error parsing DAType in configuration file!\n");
            goto parse_error;
        }
        DataAttributeDefinition* daDefinition = CidFileParser_parseDADefinition(daDefinitionNode);
        if (daDefinition == NULL)
            goto parse_error;
        Map_addEntry(daDefinitionMap, daTypeId, daDefinition);
        daDefinitionNode = mxmlFindElement(dataTypeTemplatesNode, daDefinitionNode, "DAType", NULL, NULL, MXML_DESCEND_ALL);
    }

    // parse all dataObject Definitions and store them in a map
    mxml_node_t* doDefinitionNode = mxmlFindElement(dataTypeTemplatesNode, NULL, "DOType", NULL, NULL, MXML_DESCEND_ALL);
    while (doDefinitionNode!= NULL) {
        const char* doTypeId = mxmlElementGetAttr(doDefinitionNode, "id");
        if (doTypeId == NULL) {
            if (DEBUG_IED_SERVER)
                printf("IED_SERVER: Error parsing DOType in configuration file!\n");
            goto parse_error;
        }
        DataObjectDefinition* doDefinition = CidFileParser_parseDODefinition(doDefinitionNode);
    }

parse_error:
    mxmlDelete(xmlDoc);
    Map_delete(daDefinitionMap, true);
    Map_delete(doDefinitionMap, true);
    Map_delete(lnDefinitionMap, true);
    return NULL;
}