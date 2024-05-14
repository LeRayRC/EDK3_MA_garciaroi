/**
 *
 * @brief Custom GPU camera header file.
 * @author Ivan Sancho, ESAT 2022-23
 * @subject Graphic Programming
 *
 * No OpenGL calls are needed to override "DoCull" / "DoRender" methods.
 * Just think how to fill "CamData" structure in ".cc" with the needed data
 * to render a Drawable.
 *
 */


#ifndef __CUSTOM_GPU_CAMERA_H__
#define __CUSTOM_GPU_CAMERA_H__ 1

#include "EDK3/camera.h"
#include "ESAT/math.h"
#include "EDK3/geometry.h"
#include "camera_custom.h"

namespace EDK3 {

    namespace dev {

        struct NodeData {
            EDK3::Geometry* geometry;
            EDK3::Material* material;
            EDK3::MaterialSettings* mat_settings;
            ESAT::Mat4 model;
        };

        struct CamData {
            std::vector<NodeData> data;
        };

        class CustomGPUCamera : public EDK3::CameraCustom {
        public:
            CustomGPUCamera();





            /** Determine which objects are visible */
            virtual void doCull(const Node* root_node) override;

            void doCullRecursively(const Node* node, ESAT::Mat4 parent);

            /** Renders all visible (not culled) objects */
            virtual void doRender() const override;

            /*
            Hay que rellenar esto, contiene la informacion imprescindible para pintar
            Necesita una geometria,   Material, Material Settings

            struct NodeData{
              Geometry*
              Material*
              MaterialSettings*
              Mat4 model; float[16]
            }

            struct CamData{
              std::vector<NodeData> data;
            }

            void doCullRecursively(Node* node, Mat4 parent){
              Mat4 model = parent * local_transform();

              Drawable* d = dynamic_cast<Drawable*>(node);
              if(d && d->visible){
                NodeData cmd;
                cmd.geo = d->geometry();
                cmd.mat = d->material();
                cmd.mat_set = d->material_settings();
                cmd.model = model;
                //...
                //Cuidado con los constructores de copia de las cosas por si acaso dan por culo
                data_->data.push_back(cmd);
              }
              for(0 ... node->num_children()){
                doCullRecursively(n->child(i), model);
              }
            }

            void doCull(Node* node){
              //Aqui tenemos que descartar las geometrias que no se vayan a pintar
              //Borramos el vector primero para asegurarnos que nada ha cambiado
              data->data.clear();
              doCullRecursively(Node* node Mat4identity());

            }

            void doRender(){
              // Asegurarse de esto antes de nada
              //enable depthtest
              // por defecto esta en less or equal
              // clear framebuffer



              float view[16] = view_matrix();
              float projection[16] = projection_matrix();
              for( 0 ... data.size()){
                data[i].mat->enable(data[i].mat_set);
                data[i].mat->setupCamera(projection, view);
                data[i].mat->setupModel(model);
                more ... eventual uniforms

                data[i].geo->bindAttributesAndRenderWithCurrentMaterial(data[i].mat);


              }
            }

            */

        protected:
            virtual ~CustomGPUCamera();

        private:
            CustomGPUCamera(const CustomGPUCamera&);
            CustomGPUCamera& operator=(const CustomGPUCamera&);

            EDK3::scoped_ptr<CamData> data_;

        }; //CustomGPUCamera

    } //dev

} //EDK3

#endif //__CUSTOM_GPU_CAMERA_H__