//
// Created by darkboss on 9/20/20.
//

#ifndef QUASARFX_CONFIGVALIDATORFLAGS_H
#define QUASARFX_CONFIGVALIDATORFLAGS_H

namespace quasar {
	namespace core {
		enum ConfigValidatorFlags {
			/** Validate nothing */
			CVF_VALIDATE_NONE,

			/** Validate the node's properties */
			CVF_VALIDATE_PROPS      = 1 << 1,
			/** Validate the node's children */
			CVF_VALIDATE_CHILDREN   = 1 << 2,
			/** Validate the node's value */
			CVF_VALIDATE_VALUE      = 1 << 3,
			/** Validate the node's name */
			CVF_VALIDATE_NAME       = 1 << 4,

			/** Strict validation, does not allow superfluous keys in user values */
			CVF_VALIDATE_STRICT     = 1 << 5,

			/** Strictly validate everything */
			CVF_VALIDATE_ALL_LOOSE = CVF_VALIDATE_PROPS | CVF_VALIDATE_CHILDREN | CVF_VALIDATE_VALUE | CVF_VALIDATE_NAME,
			CVF_VALIDATE_ALL_STRICT = CVF_VALIDATE_STRICT | CVF_VALIDATE_ALL_LOOSE,
		};
	}
}
#endif //QUASARFX_CONFIGVALIDATORFLAGS_H
