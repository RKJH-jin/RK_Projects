#pragma once
#include "Component.h"

/*
	=====================================================================
							행동트리란?
		root(뿌리)로 부터 원하는데로 가지(sequence, selector)를 뻗어
		잎(행동 노드, Leaf)에 있는 함수를 실행하는 방식

		장점: 분기점만 잘 설정해주면 알아서 상황에 맞는 행동을 실행시켜준다.
			  분기나 행동 노드의 추가 및 삭제가 매우 쉽다.
			 A 분기에서 사용한 행동 노드를 B 분기에서 사용하고 싶은 경우 그냥 행동노드를
			 추가해서 붙여주기만 하면 된다.(재사용/재활용이 용이하다)

		단점: 왼쪽에 있는 것부터 순서대로 판단하여 실행하기 때문에 순서를 잘 해줘야한다.

		## 언리얼에서는 기본적으로 제공하는 AI 구조이다. 현업에서도 자주 쓰이기 때문에
		알고 있으면 갸꿀!

		## C++의 List를 알고 있으면 더 이해하기 쉽다
		## List를 알려면 이진트리 구조를 알아야 더 이해가 쉽다
		## 이진트리 구조는 알고리즘에서 절! 대! 로! 빠지지 않는 대표 문제이자 개념이다!
		## 공부해두면 갸꿀!!
	=====================================================================

				<시각화를 하면 아래와 같은 형태이다!>

						<root>
						/	\
					   /     \
					  /       \
					 /         \
					/           \
		 <sequence: 분기점, 가지> \
								  \
						 <selector: 분기점, 가지>
								   /\
								  /  \
								 /    \
								/      \
		<ActionNode: 행동 노드, Leaf>    \
										 \
								<ActionNode: 행동 노드, Leaf>
*/



class TransformC;

enum class STATE : int
{
	FAILURE,	// bool값의 false
	SUCCESS,	// bool값의 true
	RUNNING,
};


//==========================================================BehaviorTree===========================================================//

/*================================================================
							AI 원형 클래스
================================================================*/

class BT : public Component
{
protected:

	
public:
	BT() {};
	~BT() {};

	/*================================================================
					형태를 제공하는 추상 클래스
	================================================================*/
	class Node
	{
	protected:
		STATE _state;
		
	public:
		virtual STATE invoke() = 0;
	};

	//==========================================================CompositeNode===========================================================//

	/*================================================================
			여러개의 자식으로 구성된 Node들을 가지고 있는 최상위 클래스
	================================================================*/
	class CompositeNode : public Node
	{
	private:
		list<Node*> lChildren;
	public:
		void AddChild(Node* node) { lChildren.emplace_back(node); }
		const list<Node*>& getChildren() { return lChildren; }
	};
	/*================================================================
						CompositeNode 카테고리 중 하나
							분기점 중 하나
				(하위 노드들 중에서 하나만 실행할 때 사용)
	================================================================*/
	class Selector : public CompositeNode // 하나라도 true면 true 반환 -> 전부 다 false면 행동 끝남
	{
	public:
		virtual STATE invoke() override
		{
			for (auto node : getChildren())
			{
				STATE temp = node->invoke();
				if (temp == STATE::RUNNING)
				{
					return STATE::RUNNING;
				}
				else if (temp == STATE::SUCCESS)
				{
					return STATE::SUCCESS;
				}
			}
			return STATE::FAILURE;
		}
	};

	/*================================================================
						CompositeNode 카테고리 중 하나
							분기점 중 하나
			(하위 노드들을 다 실행하다가 하나가 false되면 끝남)
	================================================================*/
	class Sequence : public CompositeNode // 하나라도 false면 false 반환 -> 전부 다 true면 행동 끝남
	{
	public:
		virtual STATE invoke() override
		{
			for (auto node : getChildren())
			{
				STATE temp = node->invoke();
				if (temp == STATE::RUNNING)
				{
					return STATE::RUNNING;
				}
				if (temp == STATE::FAILURE)
				{
					return STATE::FAILURE;
				}
			}
			return STATE::SUCCESS;
		}
	};
	//=====================================================Decorator=========================================================//

	/*================================================================

						하나의 자식만을 가지고 있어서
					조건에 따라 결과를 반환하는 최상위 클래스

	================================================================*/
	class DecoratorNode : public Node
	{
	private:
		Node* child;

	protected:
		Node* getChild() const { return child; }
	public:
		void AddChild(Node* node) { child = node; }
	};

	/*================================================================

				조건에 따라 자식을 실행하거나 실패를 반환

	================================================================*/
	class Condition : public DecoratorNode
	{
	private:
		function<bool(void)> fn;

	public:
		Condition() {};

		virtual STATE invoke() = 0;
	};

	class VoidCondition : public Condition
	{
	private:
		function<bool(void)> fn;

	public:
		VoidCondition(function<bool(void)> fn)
		{
			this->fn = fn;
		}
		virtual STATE invoke()
		{
			if (fn()) return getChild()->invoke();
			else return STATE::FAILURE;
		}
	};

	class StrCondition : public Condition
	{
	private:
		function<bool(string)> fn;
		string name;

	public:
		StrCondition(function<bool(string)> fn, string name)
		{
			this->fn = fn;
			this->name = name;
		}

		virtual STATE invoke()
		{
			if (fn(name)) return getChild()->invoke();
			else return STATE::FAILURE;
		}

	};

	class ToolCondition : public Condition
	{
	private:
		function<bool(TOOLTYPE)> fn;
		TOOLTYPE name;

	public:
		ToolCondition(function<bool(TOOLTYPE)> fn, TOOLTYPE name)
		{
			this->fn = fn;
			this->name = name;
		}

		virtual STATE invoke()
		{
			if (fn(name)) return getChild()->invoke();
			else return STATE::FAILURE;
		}

	};

	/*================================================================

						조건의 결과값을 반전하여 반환

	================================================================*/
	class Inverter : public DecoratorNode
	{
	private:
		virtual STATE invoke() override
		{
			if (getChild()->invoke() == STATE::SUCCESS) return STATE::FAILURE;
			else if (getChild()->invoke() == STATE::FAILURE) return STATE::SUCCESS;
		}
	};

	/*================================================================

							항상 성공을 반환

	================================================================*/
	class Suceeder : public DecoratorNode
	{
	public:
		virtual STATE invoke() override
		{
			if (getChild()->invoke() == STATE::FAILURE) return STATE::SUCCESS;
			else if (getChild()->invoke() == STATE::SUCCESS) return STATE::SUCCESS;
		}
	};

	/*================================================================

						실패를 반환할 때까지 반복 실행

	================================================================*/
	class RepeaterUntilFail : public DecoratorNode
	{
	public:
		virtual STATE invoke() override
		{
			while (getChild()->invoke() != STATE::FAILURE)
			{

			}
			return STATE::SUCCESS;
		}
	};

	//==========================================================ActionNode===========================================================//

	/*================================================================
							Node 카테고리 중 하나
				(실질적으로 행동 함수의 원형을 선언하는 클래스)
	================================================================*/
	class ActionNode : public Node
	{

	};


	
};
