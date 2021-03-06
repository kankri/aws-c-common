/*
 * Copyright 2019 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 *
 *  http://aws.amazon.com/apache2.0
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */

#include <aws/common/linked_list.h>
#include <proof_helpers/make_common_data_structures.h>

void aws_linked_list_swap_contents_harness() {
    /* data structure */
    struct aws_linked_list a, b;

    ensure_linked_list_is_allocated(&a, MAX_LINKED_LIST_ITEM_ALLOCATION);
    ensure_linked_list_is_allocated(&b, MAX_LINKED_LIST_ITEM_ALLOCATION);

    /* Keep the old first node of the linked lists. Note that we need
     * to save the old head address separately from the list itself
     * because &old_a.head != &a.head (since they are different
     * variables). */
    struct aws_linked_list_node *old_a_head = &a.head;
    struct aws_linked_list old_a = a;
    struct aws_linked_list_node *old_b_head = &b.head;
    struct aws_linked_list old_b = b;

    /* perform operation under verification */
    aws_linked_list_swap_contents(&a, &b);

    /* assertions */
    assert(aws_linked_list_is_valid(&a));
    assert(aws_linked_list_is_valid(&b));

    if (aws_linked_list_empty(&a)) {
        assert(old_b.tail.prev == old_b_head);
    } else {
        assert(a.head.next == old_b.head.next);
        assert(a.tail.prev == old_b.tail.prev);
    }

    if (aws_linked_list_empty(&b)) {
        assert(old_a.tail.prev == old_a_head);
    } else {
        assert(b.head.next == old_a.head.next);
        assert(b.tail.prev == old_a.tail.prev);
    }
}
