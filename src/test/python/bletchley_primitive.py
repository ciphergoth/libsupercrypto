import cffi

ffi = cffi.FFI()
blib = ffi.dlopen("target/lib/libbletchleyprimitives.so.1")

class Constants(object):
    def __init__(self, p):
        self.p = p

    def __getattr__(self, name):
        return getattr(blib, "cffi_{}_{}_{}".format(
            self.p.operation, self.p.primitive, name))

class Primitive(object):
    def __init__(self, operation, primitive):
        self.operation = operation
        self.primitive = primitive
        with open("target/lib/cffi_headers/bletchley/primitives/cffi_{}_{}.h".format(
            operation, primitive)) as f:
            ffi.cdef(f.read())


    def __getattr__(self, name):
        if name == "const":
            return Constants(self)
        return getattr(blib, "{}_{}_{}".format(
            self.operation, self.primitive, name))

    def __call__(self, *args, **kw):
        return getattr(blib, "{}_{}".format(
            self.operation, self.primitive))(*args, **kw)

    def __str__(self):
        return format("Primitive({}, {}, implementation={}, version={})".format(
            repr(self.operation),
            repr(self.primitive),
            repr(ffi.string(self.const.IMPLEMENTATION)),
            repr(ffi.string(self.const.VERSION))))
