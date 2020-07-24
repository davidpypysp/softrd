import React, { useState } from "react";
import { Tree, Classes, ITreeNode } from "@blueprintjs/core";
import { useSelector, useDispatch } from "react-redux";
import { RootState } from "src/store";
import { selectObject } from "src/store/objectSelector";
import { ObjectListState } from "src/store/objectList";

const SceneMenu = () => {
    const analysisNodes = (nodes: ObjectListState) => {
        const treeNodes = [];
        for (const node of Object.values(nodes)) {
            const tempNode: any = node;
            const treeNode: { [key: string]: any } = {
                label: node.name,
                id: node.id,
                icon: "document",
            };

            // if (node.children) {
            //     treeNode.childNodes = this.analysisNodes(node.children);
            //     treeNode.icon = "folder-close";
            //     treeNode.isExpanded = true;
            // } else {
            //     treeNode.icon = "document";
            // }
            treeNodes.push(treeNode);
        }
        return treeNodes;
    };

    const dispatch = useDispatch();
    const objectList = useSelector((state: RootState) => state.objectList);
    const [nodes, setNodes] = useState(analysisNodes(objectList));

    const forEachNode = (
        nodes: ITreeNode[],
        callback: (node: ITreeNode) => void
    ) => {
        if (!nodes) {
            return;
        }
        for (const node of nodes) {
            callback(node);
            forEachNode(node.childNodes, callback);
        }
    };

    const handleNodeClick = (
        nodeData: ITreeNode,
        _nodePath: number[],
        e: React.MouseEvent<HTMLElement>
    ) => {
        const originallySelected = nodeData.isSelected;
        if (!e.shiftKey) {
            forEachNode(nodes, (n) => (n.isSelected = false));
        }
        nodeData.isSelected =
            originallySelected === null ? true : !originallySelected;

        dispatch(
            selectObject(nodeData.isSelected ? String(nodeData.id) : null)
        );

        setNodes(nodes);
    };

    const handleNodeCollapse = (nodeData: ITreeNode) => {
        nodeData.isExpanded = false;
        setNodes(nodes);
    };

    const handleNodeExpand = (nodeData: ITreeNode) => {
        nodeData.isExpanded = true;
        setNodes(nodes);
    };

    return (
        <div>
            <Tree
                contents={nodes}
                onNodeClick={handleNodeClick}
                onNodeCollapse={handleNodeCollapse}
                onNodeExpand={handleNodeExpand}
                className={Classes.ELEVATION_0}
            />
        </div>
    );
};

export default SceneMenu;
