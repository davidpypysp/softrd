import React from "react";

import {
    Card, Button, Tree,
    Icon, Tooltip, Intent,
    Classes, Position, ITreeNode
} from "@blueprintjs/core";

import { connect, ConnectedProps } from 'react-redux'
import { selectObject } from "src/store/actions/objectSelector";



const mapDispatchToProps = dispatch => ({
    selectObject: (id) => dispatch(selectObject(id))
});

const connector = connect(null, mapDispatchToProps);

type SceneMenuProps = { nodes: any[] } & ConnectedProps<typeof connector>;

class SceneMenu extends React.Component<SceneMenuProps, {}> {
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
                treeNode.isExpanded = true;
            } else {
                treeNode.icon = "document";
            }
            treeNodes.push(treeNode);
        }
        return treeNodes;
    }

    public state: {
        nodes: ITreeNode[];
    } = { nodes: this.analysisNodes(this.props.nodes) };

    private handleNodeClick = (nodeData: ITreeNode, _nodePath: number[], e: React.MouseEvent<HTMLElement>) => {
        const originallySelected = nodeData.isSelected;
        if (!e.shiftKey) {
            this.forEachNode(this.state.nodes, n => (n.isSelected = false));
        }
        nodeData.isSelected = originallySelected == null ? true : !originallySelected;

        this.props.selectObject(nodeData.isSelected ? nodeData.label : null);

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

export default connect(null, mapDispatchToProps)(SceneMenu);
