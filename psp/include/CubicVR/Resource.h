#pragma once


#include <CubicVR/datatree/DataTree.h>
#include <string>
#include <fstream>


class Resource
{
protected:
	DataTree *properties;
	DataTree *header;
	
	std::string idName;
	std::string typeName;
	std::string bundleName;
	std::string sourceFile;
	const std::string tmpString;
	bool loaded;
	bool initialized;
	class ResourceManager *rm;
	
public:
	
	Resource();
	~Resource();
	DataTree &getHeader();
	DataTree &getProperties();
	void Dump();
	
	// read file type and id name without actually opening it
	static bool GetFileHeader(const std::string& filename, DataTree &fileHeader_out);
	// load file header without opening properties data
	bool LoadFileHeader(const std::string& filename);
	bool LoadFileProperties();
	bool LoadFromFile(const std::string& filename);
	bool LoadFromFileXML(const std::string& filename);
	bool SaveToFileXML(const std::string& filename);	
	bool SaveToFile(const std::string& filename);	
	bool Import(Resource &res_import);
	void UnLink();
	
	std::string &getSourceFile();
	
	bool headerLoaded();
	bool propertiesLoaded();
	
	virtual void setId(const std::string &id_in);
	virtual void setType(const std::string &typeName_in);
	virtual void setBundle(const std::string &bundleName_in);
	
	virtual std::string getId();
	virtual std::string getType();
	virtual std::string getSubType();
	virtual std::string getBundle();
	
	virtual bool isLoaded();
	virtual bool isInitialized();
	
	virtual bool init();
	virtual bool destroy();
	virtual bool reload();
	
	virtual bool onLoad();
	virtual bool onSave();
	
	void setManager(class ResourceManager *rm_in);
	class ResourceManager *getManager();
	
	inline void setInit(bool init_in) { initialized = init_in; };
};

