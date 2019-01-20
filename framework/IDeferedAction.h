#pragma once

namespace newNav {
namespace framework {

class IComponentManager;

///
/// Definition of a defered action to be executed in the
/// component manager main loop context.
///
class IDeferedAction
{
// Operation
public:

    /// Execute the action.
    ///
    /// @param manager Reference to the component manager.
    virtual void	execute(
        IComponentManager&  manager) = 0;
};

} // namespace framework
} // namespace newNav
