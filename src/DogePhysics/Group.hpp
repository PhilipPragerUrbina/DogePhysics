//
// Created by Philip on 1/9/2023.
//

#pragma once

#include <vector>
#include <memory>

namespace Doge {

    /**
     * Contains a group of references of a given object type
     * @param ObjectType The type of object to contain. Usually a form of physics object
     */
    template <class ObjectType>  class  Group {
    private:
        std::vector<std::shared_ptr<ObjectType>> objects;
    public:

        /**
         * Add an object to this group
         * @param object Reference to the object.
         * @warning Do not add same object multiple times
         */
        void add(const std::shared_ptr<ObjectType>& object_ref){
            objects.push_back(object_ref);
        }

        /**
         * Search for reference to object and remove it
         * @param object_ref The object to remove from group
         */
        void remove(const std::shared_ptr<ObjectType>& object_ref){
            for (int i = 0; i < objects.size(); i++) {
                if(objects[i] == object_ref){
                    objects.erase(i);
                    return;
                }
            }
        }

    protected:
        /**
         * Get the # of objects
         */
        unsigned int getSize() const {
            return objects.size();
        }

        /**
         * Get a raw pointer to an object
         * @param idx The index of the object
         */
        ObjectType* get(unsigned int idx){
            return objects[idx].get();
        }

        //todo doc
        std::vector<std::shared_ptr<ObjectType>>* getObjects(){
            return &objects;
        }


    };

} // Doge
