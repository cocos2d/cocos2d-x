import os
import sys

from xml.dom import minidom

def os_is_win32():
    return sys.platform == 'win32'

def os_is_mac():
    return sys.platform == 'darwin'

class VCXProject(object):
    def __init__(self, proj_file_path):
        self.xmldoc = minidom.parse(proj_file_path)
        self.root_node = self.xmldoc.documentElement
        if os.path.isabs(proj_file_path):
            self.file_path = proj_file_path
        else:
            self.file_path = os.path.abspath(proj_file_path)

    def get_or_create_node(self, parent, node_name, create_new=True):
        children = parent.getElementsByTagName(node_name)
        if len(children) > 0:
            return children[0]
        else:
            if create_new:
                child = parent.createElement(node_name)
                return child
            else:
                return None

    def save(self, new_path=None):
        if new_path is None:
            savePath = self.file_path
        else:
            if os.path.isabs(new_path):
                savePath = new_path
            else:
                savePath = os.path.abspath(new_path)

        print("Saving the vcxproj to %s" % savePath)

        if not os.path.isabs(savePath):
            savePath = os.path.abspath(savePath)

        file_obj = open(savePath, "w")
        self.xmldoc.writexml(file_obj, encoding="utf-8")
        file_obj.close()

        file_obj = open(savePath, "r")
        file_content = file_obj.read()
        file_obj.close()

        file_content = file_content.replace("&quot;", "\"")
        file_content = file_content.replace("/>", " />")

        if os_is_mac():
            file_content = file_content.replace("\n", "\r\n")

        file_content = file_content.replace("?><", "?>\r\n<")

        file_obj = open(savePath, "w")
        file_obj.write(file_content)
        file_obj.close()

        print("Saving Finished")

    def remove_lib(self, lib_name):
        cfg_nodes = self.root_node.getElementsByTagName("ItemDefinitionGroup")
        for cfg_node in cfg_nodes:
            cond_attr = cfg_node.attributes["Condition"].value
            if cond_attr.lower().find("debug") >= 0:
                cur_mode = "Debug"
            else:
                cur_mode = "Release"

            # remove the linked lib config
            link_node = self.get_or_create_node(cfg_node, "Link")
            depends_node = self.get_or_create_node(link_node, "AdditionalDependencies")
            link_info = depends_node.firstChild.nodeValue
            cur_libs = link_info.split(";")
            link_modified = False

            if lib_name in cur_libs:
                print("Remove linked library %s from \"%s\" configuration" % (lib_name, cur_mode))
                cur_libs.remove(lib_name)
                link_modified = True

            if link_modified:
                link_info = ";".join(cur_libs)
                depends_node.firstChild.nodeValue = link_info

    def add_lib(self, lib_name):
        cfg_nodes = self.root_node.getElementsByTagName("ItemDefinitionGroup")
        for cfg_node in cfg_nodes:
            cond_attr = cfg_node.attributes["Condition"].value
            if cond_attr.lower().find("debug") >= 0:
                cur_mode = "Debug"
            else:
                cur_mode = "Release"

            # add the linked lib config
            link_node = self.get_or_create_node(cfg_node, "Link")
            depends_node = self.get_or_create_node(link_node, "AdditionalDependencies")
            link_info = depends_node.firstChild.nodeValue
            cur_libs = link_info.split(";")
            link_modified = False
            if lib_name not in cur_libs:
                print("Add linked library %s for \"%s\" configuration" % (lib_name, cur_mode))
                cur_libs.insert(0, lib_name)
                link_modified = True

            if link_modified:
                link_info = ";".join(cur_libs)
                depends_node.firstChild.nodeValue = link_info

    def get_event_command(self, event, config=None):
        cfg_nodes = self.root_node.getElementsByTagName("ItemDefinitionGroup")
        ret = ""
        for cfg_node in cfg_nodes:
            if config is not None:
                cond_attr = cfg_node.attributes["Condition"].value
                if cond_attr.lower().find("debug") >= 0:
                    cur_mode = "Debug"
                else:
                    cur_mode = "Release"

                if cur_mode.lower() != config.lower():
                    continue

            event_nodes = cfg_node.getElementsByTagName(event)
            if len(event_nodes) <= 0:
                continue

            event_node = event_nodes[0]
            cmd_nodes = event_node.getElementsByTagName("Command")
            if len(cmd_nodes) <= 0:
                continue

            cmd_node = cmd_nodes[0]
            ret = cmd_node.firstChild.nodeValue
            break

        return ret

    def set_event_command(self, event, command, config=None, create_new=True):
        cfg_nodes = self.root_node.getElementsByTagName("ItemDefinitionGroup")
        for cfg_node in cfg_nodes:
            if config is not None:
                if 'Condition' not in cfg_node.attributes.keys():
                    continue

                cond_attr = cfg_node.attributes["Condition"].value
                if cond_attr.lower().find("debug") >= 0:
                    cur_mode = "Debug"
                else:
                    cur_mode = "Release"

                if cur_mode.lower() != config.lower():
                    continue

            event_node = self.get_or_create_node(cfg_node, event, create_new)
            if event_node is None:
                continue

            cmd_node = self.get_or_create_node(event_node, "Command")
            if cmd_node.firstChild is None:
                impl = minidom.getDOMImplementation()
                dom = impl.createDocument(None, 'catalog', None)
                nodeValue = dom.createTextNode(command)
                cmd_node.appendChild(nodeValue)
            else:
                cmd_node.firstChild.nodeValue = command

    def get_node_if(self, parent, name):
        children = parent.getElementsByTagName(name)
        child = None
        if len(children) > 0:
            child = children[0]
        else:
            child = self.xmldoc.createElement(name)
            parent.appendChild(child)
        return child

    def set_item(self, event, eventItem, command):
        cfg_nodes = self.root_node.getElementsByTagName("ItemDefinitionGroup")
        for cfg_node in cfg_nodes:
            cond_attr = cfg_node.attributes["Condition"].value
            if cond_attr.lower().find("debug") >= 0:
                cur_mode = "Debug"
            else:
                cur_mode = "Release"

            print("event: %s" % event)
            event_node = self.get_node_if(cfg_node, event)
            cmd_node = self.get_node_if(event_node, eventItem)
            text_node = self.xmldoc.createTextNode(command)
            cmd_node.appendChild(text_node)

    def set_include_dirs(self, paths):
        if "%(AdditionalIncludeDirectories)" not in paths:
            paths.append("%(AdditionalIncludeDirectories)")

        include_value = ";".join(paths)
        include_value = include_value.replace("/", "\\")
        cfg_nodes = self.root_node.getElementsByTagName("ItemDefinitionGroup")
        for cfg_node in cfg_nodes:
            compile_node = self.get_or_create_node(cfg_node, "ClCompile")
            include_node = self.get_or_create_node(compile_node, "AdditionalIncludeDirectories")
            include_node.firstChild.nodeValue = include_value

    def remove_proj_reference(self):
        itemgroups = self.root_node.getElementsByTagName("ItemGroup")
        for item in itemgroups:
            proj_refers = item.getElementsByTagName("ProjectReference")
            if len(proj_refers) > 0:
                self.root_node.removeChild(item)

    def remove_predefine_macro(self, macro, config=None):
        cfg_nodes = self.root_node.getElementsByTagName("ItemDefinitionGroup")
        for cfg_node in cfg_nodes:
            if config is not None:
                if 'Condition' not in cfg_node.attributes.keys():
                    continue

                cond_attr = cfg_node.attributes["Condition"].value
                if cond_attr.lower().find("debug") >= 0:
                    cur_mode = "Debug"
                else:
                    cur_mode = "Release"

                if (cur_mode.lower() != config.lower()):
                    continue

            compile_node = self.get_or_create_node(cfg_node, "ClCompile")
            predefine_node = self.get_or_create_node(compile_node, "PreprocessorDefinitions")
            defined_values = predefine_node.firstChild.nodeValue

            defined_list = defined_values.split(";")
            if macro in defined_list:
                defined_list.remove(macro)
                new_value = ";".join(defined_list)
                predefine_node.firstChild.nodeValue = new_value
