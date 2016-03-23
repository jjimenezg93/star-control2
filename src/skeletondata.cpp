#include "../include/skeletondata.h"
#include "../include/image.h"
#include "../include/string.h"
#include "../lib/rapidxml.hpp"

using namespace rapidxml;

SkeletonData::SkeletonData(const String& filename) {
	// Cargamos el string
    String buffer = String::Read(filename);
	if ( buffer != "" ) {
		// Analizamos el XML
		xml_document<> doc;
        doc.parse<0>((char*)buffer.ToCString());
		xml_node<>* rootNode = doc.first_node();

		// Leemos configuracion de los huesos
		xml_node<>* boneNode = rootNode->first_node("Bone");
		while ( boneNode != NULL ) {
            String id = boneNode->first_attribute("m_id")->value();
            String parentName = boneNode->first_attribute("parent")->value();
            String imageName = boneNode->first_attribute("m_image")->value();
			double pivotx = atof(boneNode->first_attribute("pivot_x")->value());
			double pivoty = atof(boneNode->first_attribute("pivot_y")->value());
			double handlex = atof(boneNode->first_attribute("handle_x")->value());
			double handley = atof(boneNode->first_attribute("handle_y")->value());

			BoneData boneData(id, parentName, imageName, pivotx, pivoty, handlex, handley);

			// Leemos los frames del hueso
			xml_node<>* frameNode = boneNode->first_node("frame");
			while ( frameNode != NULL ) {
				xml_node<>* translateNode = frameNode->first_node("translate");
				xml_node<>* rotateNode = frameNode->first_node("rotate");
				xml_node<>* scaleNode = frameNode->first_node("scale");
				int32 id = (int32)(atof(frameNode->first_attribute("m_id")->value()) - 1);
				double translatex = atof(translateNode->first_attribute("m_x")->value());
				double translatey = atof(translateNode->first_attribute("m_y")->value());
				double rotate = atof(rotateNode->first_attribute("z")->value());
				double scalex = atof(scaleNode->first_attribute("m_x")->value());
				double scaley = atof(scaleNode->first_attribute("m_y")->value());

                Frame frame(id, translatex, translatey, rotate, scalex, scaley);
                boneData.AddFrame(frame);

				frameNode = frameNode->next_sibling("frame");
			}

            boneDatas.Add(boneData);

			boneNode = boneNode->next_sibling("Bone");
		}
	}
}
