import React from "react";

import { Tree, Classes, ITreeNode } from "@blueprintjs/core";
import { connect, ConnectedProps } from 'react-redux'
import { selectObject } from "src/store/actions/objectSelector";
import { ObjectListState } from "src/store/reducers/objectList";

const mapStateToProps = (state) => {
    const { objectList } = state;
    return { objectList }
};
const mapDispatchToProps = dispatch => ({
    selectObject: id => dispatch(selectObject(id))
});
const connector = connect(mapStateToProps, mapDispatchToProps);

type SceneMenuProps = ConnectedProps<typeof connector>;

class SceneMenu extends React.Component<SceneMenuProps, {}> {
    private analysisNodes = (nodes: ObjectListState) => {
        const treeNodes = [];
        for (let node of Object.values(nodes)) {
            const tempNode: any = node;
            const treeNode: { [key: string]: any } = {
                label: node.name,
                id: node.id,
                icon: "document"
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
    }

    public state: {
        nodes: ITreeNode[];
    } = { nodes: this.analysisNodes(this.props.objectList) };

    private handleNodeClick = (nodeData: ITreeNode, _nodePath: number[], e: React.MouseEvent<HTMLElement>) => {
        const originallySelected = nodeData.isSelected;
        if (!e.shiftKey) {
            this.forEachNode(this.state.nodes, n => (n.isSelected = false));
        }
        nodeData.isSelected = originallySelected == null ? true : !originallySelected;

        this.props.selectObject(nodeData.isSelected ? nodeData.id : null);

        this.setState(this.state);
    };

    private handleNodeCollapse = (nodeData: ITreeNode) => {
        nodeData.isExpanded = false;
        this.setState(this.state);
    };

    private handleNodeExpand = (nodeData: ITreeNode) => {
        nodeData.isExpanded = true;
        this.setState(this.state);
    };

    private forEachNode(nodes: ITreeNode[], callback: (node: ITreeNode) => void) {
        if (nodes == null) {
            return;
        }

        for (const node of nodes) {
            callback(node);
            this.forEachNode(node.childNodes, callback);
        }
    }

    render() {
        return (
            <div>
                <Tree
                    contents={this.state.nodes}
                    onNodeClick={this.handleNodeClick}
                    onNodeCollapse={this.handleNodeCollapse}
                    onNodeExpand={this.handleNodeExpand}
                    className={Classes.ELEVATION_0}
                />
            </div>
        );
    }
}

export default connector(SceneMenu);
