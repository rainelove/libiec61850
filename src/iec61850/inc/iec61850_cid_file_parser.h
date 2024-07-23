#ifndef CID_FILE_PARSER_H_
#define CID_FILE_PARSER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "stdio.h"

/** \addtogroup server_api_group
 * @{
 */

/** \defgroup CID_FILE_PARSER Create data models by CID files
 * @{
 */

/**
 * \brief IEC61850 Type Declaration type
 */

typedef struct sDataAttributeDefinition DataAttributeDefinition;

typedef struct sDataObjectDefinition DataObjectDefinition;

typedef struct sLogicalNodeDefinition LogicalNodeDefinition;

struct sDataAttributeDefinition {
    char* name;
    FunctionalConstraint fc;
    DataAttributeType attributeType;
    uint8_t triggerOptions;
};

struct sDataObjectDefinition {
    char* cdc;
    LinkedList attributes;
};

struct sLogicalNodeDefinition {
    LinkedList dataObjects;
};


/**
 * \brief Create a data model from CID file
 *
 * \param filename name or path of the CID file
 *
 * \return the data model to be used by \ref IedServer
 */

LIB61850_API IedModel*
CidFileParser_createModelFromCidFileEx(const char* filename);

LIB61850_API IedModel*
CidFileParser_createModelFromCidFile(FILE* fileHandle);

/**@}*/

/**@}*/

#ifdef __cplusplus
}
#endif

#endif
