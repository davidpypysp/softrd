import React from "react";

import {
    Card, Button, Tree,
    Icon, Tooltip, Intent,
    Classes, Position
} from "@blueprintjs/core";





export interface SceneMenuProps { nodes: any[] }

export default class SceneMenu extends React.Component<SceneMenuProps, {}> {
    // public nodes: any[] = [
    //     {
    //         id: 0,
    //         hasCaret: true,
    //         icon: "folder-close",
    //         label: "Folder 0",
    //     },
    //     {
    //         id: 1,
    //         icon: "folder-close",
    //         isExpanded: true,
    //         label: "tree",
    //         childNodes: [
    //             {
    //                 id: 2,
    //                 icon: "document",
    //                 label: "Item 0",
    //                 secondaryLabel: (
    //                     <Tooltip content="An eye!">
    //                         <Icon icon="eye-open" />
    //                     </Tooltip>
    //                 ),
    //             },
    //             {
    //                 id: 3,
    //                 icon: <Icon icon="tag"
    //                     intent={Intent.PRIMARY}
    //                     className={Classes.TREE_NODE_ICON} />,
    //                 // label: "Organic meditation gluten-free,
    //                 // sriracha VHS drinking vinegar beard man.",
    //             },
    //             {
    //                 id: 4,
    //                 hasCaret: true,
    //                 icon: "folder-close",
    //                 label: (
    //                     <Tooltip content="foo" position={Position.RIGHT}>
    //                         Folder 2
    //                     </Tooltip>
    //                 ),
    //                 childNodes: [
    //                     { id: 5, label: "No-Icon Item" },
    //                     { id: 6, icon: "tag", label: "Item 1" },
    //                     {
    //                         id: 7,
    //                         hasCaret: true,
    //                         icon: "folder-close",
    //                         label: "Folder 3",
    //                         childNodes: [
    //                             {
    //                                 id: 8,
    //                                 icon: "document",
    //                                 label: "Item 0"
    //                             },
    //                             {
    //                                 id: 9,
    //                                 icon: "tag",
    //                                 label: "Item 1"
    //                             },
    //                         ],
    //                     },
    //                 ],
    //             },
    //         ],
    //     },
    //     {
    //         id: 2,
    //         hasCaret: true,
    //         icon: "folder-close",
    //         label: "Super secret files",
    //         disabled: true,
    //     },
    // ];

    private analysisNodes = (nodes: any[]) => {
        const treeNodes: any[] = [];
        for (let node of nodes) {
            const treeNode: { [key: string]: any } = {
                label: node.name,
                id: node.name
            };

            if (node.children) {
                treeNode.childNodes = this.analysisNodes(node.children);
                treeNode.icon = "folder-close";
            } else {
                treeNode.icon = "document";
            }
            treeNodes.push(treeNode);
        }
        return treeNodes;
    }

    render() {
        return (
            <div>
                <Tree
                    contents={this.analysisNodes(this.props.nodes)}
                    className={Classes.ELEVATION_0}
                />
            </div>
        );
    }
}


