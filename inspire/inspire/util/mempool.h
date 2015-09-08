#ifndef _INSPIRE_UTIL_ENTITY_ALLOCATOR_H_
#define _INSPIRE_UTIL_ENTITY_ALLOCATOR_H_

#include "mutex.h"

namespace inspire {

   template <class TEntity>
   class EntityFactory : public noncopyable
   {
   public:
      EntityFactory() : _count(0), _hdrFree(NULL)
      {
         _entitySize = sizeof(TEntity) > sizeof(TEntity*) ? sizeof(TEntity) : sizeof(TEntity*);
      }

      ~EntityFactory()
      {
         while (_hdrFree)
         {
            TEntity* toFree = _hdrFree;
            _hdrFree = *(reinterpret_cast<TEntity**>(_hdrFree));
            ::free(toFree);
         }
      }

      TEntity* create()
      {
         scopeLock(&_mtx);
         ++count;
         if (NULL == _hdrFree)
         {
            void* ptr = ::malloc(_entitySize);
            if (NULL == ptr)
            {
               LogError("Failed to alloc memory, out of memory");
               return NULL;
            }
            return new(ptr)TEntity;
         }

         TEntity* entity = _hdrFree;
         _hdrFree = *(reinterpret_cast<TEntity**>(_hdrFree));
         return new(entity)TEntity;
      }

      TEntity* create(const TEntity* entity)
      {
         scopeLock(&_mtx);
         ++count;
         if (NULL == _hdrFree)
         {
            void* ptr = ::malloc(_entitySize);
            if (NULL == ptr)
            {
               LogError("Failed to alloc memory, out of memory");
               return NULL;
            }
            return new(ptr)TEntity(entity);
         }

         TEntity* buffer = _hdrFree;
         _hdrFree = *(reinterpret_cast<TEntity**>(_hdrFree));
         return new(buffer)TEntity(entity);
      }

      void dealloc(TEntity* entity)
      {
         entity->~TEntity();
         do
         {
            scopeLock(&_mtx);
            ::memset(entity, 0xfe, _entitySize);
            --_count;
            INSPIRE_ASSERT(_count >= 0);
            *(reinterpret_cast<TEntity**>(entity)) = _hdrFree;
            _hdrFree = entity;
         } while (true);
      }

   private:
      unsigned int _count;
      unsigned int _entitySize;
      TEntity*     _hdrFree;
      insMutex     _mtx;
   };

}
#endif