#include <cassert>
#include "permissions.h"

using namespace std::literals;

int main() {
    {
        FileAccess file;
        file.SetPermission(Permissions::READ);
        assert(file.CheckPermission(Permissions::READ));
        assert(!file.CheckPermission(Permissions::WRITE));
        assert(!file.CheckPermission(Permissions::EXECUTE));
        assert((file.ToString() == "0001"s ));

        file.SetPermission(Permissions::EXECUTE);
        assert((file.ToString() == "0101"s ));
        assert(file.CheckPermission(Permissions::READ));
        assert(!file.CheckPermission(Permissions::WRITE));
        assert(file.CheckPermission(Permissions::EXECUTE));

        file.SetPermission(Permissions::WRITE);
        assert((file.ToString() == "0111"s ));
        assert(file.CheckPermission(Permissions::READ));
        assert(file.CheckPermission(Permissions::WRITE));
        assert(file.CheckPermission(Permissions::EXECUTE));

        file.RemovePermission(Permissions::EXECUTE);
        assert((file.ToString() == "0011"s ));
        assert(file.CheckPermission(Permissions::READ));
        assert(file.CheckPermission(Permissions::WRITE));
        assert(!file.CheckPermission(Permissions::EXECUTE));

        file.RemovePermission(Permissions::READ);
        assert((file.ToString() == "0010"s ));
        assert(!file.CheckPermission(Permissions::READ));
        assert(file.CheckPermission(Permissions::WRITE));
        assert(!file.CheckPermission(Permissions::EXECUTE));

        file.RemovePermission(Permissions::WRITE);
        assert((file.ToString() == "0000"s ));
        assert(!file.CheckPermission(Permissions::READ));
        assert(!file.CheckPermission(Permissions::WRITE));
        assert(!file.CheckPermission(Permissions::EXECUTE));
    } {
        FileAccess file;
        file.SetPermission(Permissions::WRITE);
        file.TogglePermission(Permissions::WRITE);
        assert((file.ToString() == "0000"s ));

        file.SetPermission(Permissions::READ);
        file.TogglePermission(Permissions::WRITE);
        assert((file.ToString() == "0011"s ));

        file.TogglePermission(Permissions::READ);
        file.TogglePermission(Permissions::EXECUTE);
        assert((file.ToString() == "0110"s ));

        file.TogglePermission(Permissions::WRITE);
        file.TogglePermission(Permissions::EXECUTE);
        assert((file.ToString() == "0000"s ));
    }
}
