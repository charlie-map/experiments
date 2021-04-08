const MAX_DEGREE = 3;

// root node structure
function node_factory() {
	return {
		keys: [],
		children: []
	}
}

function insert(node, key) {
	// recursively find the spot for this key and put it there
	// call splitChild on it as you come back up.
	// find the child node where this key would slot

	// base case
	if (!node.children.length) {
		node = spliceElement(node, key);
		return splitChild(node);
	}

	for (let i = 0; i <= node.keys.length; i++) {
		if ((i < node.keys.length && key < node.keys[i]) || i == node.keys.length) {
			let split = insert(node.children[i], key);
			// if the insertion at this level required splitting, we need to merge this "subtree" with this node
			if (split)
				merge(node, i);
			if(splitChild(node))
				return node;
			else
				return null;
		}
	}
}

function merge(node, split_posn) {
	let split_node = node.children[split_posn]; // 7 -> 6, -> 8
	node.keys[split_posn] = split_node.keys[0];
	node.children[split_posn] = split_node.children[0];
	node.children[split_posn+1] = split_node.children[1];
}

function spliceElement(node, key) {
	// find correct location for key in this node
	// invariant: we always assume there's space for this key in the node
	// if there isn't, splitChild will clean up after us.
	if (!node.keys) {
		node.keys[0] = key;
		return node;
	}
	for (let i = 0; i < node.keys.length; i++) {
		if (key < node.keys[i]) {
			node.keys.splice(i, 0, key);
			return node;
		}
	}
	node.keys.push(key);
	return node;
}

function splitChild(node) {
	// in general, the btree grows UPWARD after hitting base case
	// this helper function will:
	// split a full node (leaf or otherwise) into a node with a single key and two children
	// return the node with the single key and two children
	// the overall traversal algo will then use this at each level to "correct"
	// as the recursion comes back up the stack

	// fullness check -- no split needed
	if (node.children.length <= MAX_DEGREE && node.keys.length <= MAX_DEGREE - 1) return null;

	// split if needed
	let midpt_key = Math.floor(MAX_DEGREE/2);
	let midpt_child = Math.floor(MAX_DEGREE/2);
	let left = node_factory();
	let right = node_factory();

	// construct left and right children properly with splice
	left.children = node.children.splice(0, midpt_child);
	right.children = node.children.splice(0);
	left.keys = node.keys.splice(0, midpt_key);
	right.keys = node.keys.splice(1);

	// construct new parent node and pass it back
	node.children = [left, right];
	return node;
}

/*let fake_test_node = node_factory();

fake_test_node.keys = [3,5,8];
fake_test_node.children = [node_factory(), node_factory(), node_factory(), node_factory()];
fake_test_node = splitChild(fake_test_node);

console.log(JSON.stringify(fake_test_node));*/
let root = node_factory();
insert(root, 3);
insert(root, 5);
insert(root, 8);
insert(root, 6);
insert(root, 7);
insert(root, 8);
insert(root, 9);
insert(root, 10);
console.log(JSON.stringify(root));