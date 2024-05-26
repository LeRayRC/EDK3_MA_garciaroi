#include "dev/custom_gpu_camera.h"

#include <vector>

#include "dev/custom_gpu_manager.h"
#include "EDK3/geometry.h"
#include "EDK3/material.h"
#include "EDK3/materialsettings.h"
#include "ESAT/math.h"
#include "EDK3/node.h"
#include "EDK3/drawable.h"
#include "EDK3/dev/glew.h"

namespace EDK3 {


	namespace dev {

		

		CustomGPUCamera::CustomGPUCamera(){
			data_.alloc();
		}

		CustomGPUCamera::~CustomGPUCamera(){}

		CustomGPUCamera::CustomGPUCamera(const CustomGPUCamera& other){
			data_->data = other.data_->data;
		}
		CustomGPUCamera& CustomGPUCamera::operator=(const CustomGPUCamera& other){
			data_->data = other.data_->data;
			return *this;
		}

		void CustomGPUCamera::doCullRecursively(const Node* node, ESAT::Mat4 parent) {
			//float model[16] 
			ESAT::Mat4 model;
			ESAT::Mat4 local_transform_matrix;
			const float* local_transform_pointer = node->local_transform();
			for (int i = 0; i < 16; i++) {
				local_transform_matrix.d[i] = local_transform_pointer[i];
			}
			model = ESAT::Mat4Multiply(parent, local_transform_matrix);
			
			EDK3::Node* n = const_cast<EDK3::Node*>(node);
			EDK3::Drawable* d = dynamic_cast<EDK3::Drawable*>(n);
			if (d && d->visible()) {
				NodeData node_data;
				node_data.geometry = d->geometry();
				node_data.material = d->material();
				node_data.mat_settings = d->material_settings();
				node_data.model = model;
				data_->data.push_back(node_data);
			}
			for (unsigned int i = 0; i < node->num_children(); i++) {
				doCullRecursively(node->child(i), model);
			}
		}

		void CustomGPUCamera::doCull(const Node* root_node) {
			data_->data.clear();
			doCullRecursively(root_node, ESAT::Mat4Identity());
		}

		void CustomGPUCamera::doRender() const{
			const float* view = view_matrix();
			const float* projection = projection_matrix();

			float rgba[4] = { 1.0f,1.0f,1.0f,1.0f };
			EDK3::dev::GPUManager& GPU = *EDK3::dev::GPUManager::Instance();
			//GPU.clearFrameBuffer(rgba);
			//GPU.enableDepthTest(EDK3::dev::GPUManager::CompareFunc::kCompareFunc_LessOrEqual);


			for (unsigned int i = 0; i < data_->data.size(); i++) {
				data_->data[i].material->enable(data_->data[i].mat_settings);
				data_->data[i].material->setupCamera(projection, view);
				data_->data[i].material->setupModel(data_->data[i].model.d);

				data_->data[i].geometry->bindAttributesAndRenderWithCurrentMaterial(data_->data[i].material);
			}
		}
	}
}
